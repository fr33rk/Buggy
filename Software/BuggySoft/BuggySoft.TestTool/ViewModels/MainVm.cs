using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Prism;
using Prism.Commands;
using Prism.Regions;

namespace BuggySoft.TestTool.ViewModels
{
	/// <summary>View model for the main view.
	/// </summary>
	/// <seealso cref="ViewModelBase" />
	/// <seealso cref="INavigationAware" />
	public class MainVm : ViewModelBase, INavigationAware
	{
		#region Definitions

		private readonly IBuggyCommunicationService mComService;
		private readonly IBuggySoftSettingsService mSettings;

		#endregion Definitions

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="MainVm"/> class.
		/// </summary>
		/// <param name="buggyCommunicationService">The buggy communication service.</param>
		/// <param name="settingsService">The settings service.</param>
		public MainVm(IBuggyCommunicationService buggyCommunicationService, IBuggySoftSettingsService settingsService)
		{
			mSettings = settingsService;
			mComService = buggyCommunicationService;
			mComService.MessageReceived += ComServiceOnMessageReceived;
			mComService.MessageSend += ComServiceOnMessageSend;
			mComService.Connected += ComServiceOnConnected;
			mComService.Disconnected += ComServiceOnDisconnected;
		}

		#endregion Constructor(s)

		#region ComService

		private void ComServiceOnDisconnected(object sender, EventArgs eventArgs)
		{
			// ReSharper disable once ExplicitCallerInfoArgument
			NotifyPropertyChanged(nameof(IsConnected));
		}

		private void ComServiceOnConnected(object sender, EventArgs eventArgs)
		{
			IsConnecting = false;

			// ReSharper disable once ExplicitCallerInfoArgument
			NotifyPropertyChanged(nameof(IsConnected));
		}

		private void ComServiceOnMessageReceived(object sender, MessageReceivedEventArgs<BaseBuggyMessageWrapper> messageReceivedEventArgs)
		{
			Application.Current.Dispatcher.Invoke(() => Messages.Insert(0, new MessageVm(true, messageReceivedEventArgs.Message)));
			//Application.Current.Dispatcher.Invoke(() => Messages.Add(new MessageVm(true, messageReceivedEventArgs.Message)));
		}

		private void ComServiceOnMessageSend(object sender, MessageSendEventArgs messageSendEventArgs)
		{
			Application.Current.Dispatcher.Invoke(() => Messages.Insert(0, new MessageVm(false, messageSendEventArgs.Message)));
			//Application.Current.Dispatcher.Invoke(() => Messages.Add(new MessageVm(false, messageSendEventArgs.Message)));
		}

		#endregion ComService

		#region Property Messages

		/// <summary>List of messages send to and received from the buggy.
		/// </summary>
		public ObservableCollection<MessageVm> Messages { get; } = new ObservableCollection<MessageVm>();

		#endregion Property Messages

		#region INavigationAware

		/// <summary>Called when the implementer has been navigated to.
		/// </summary>
		/// <param name="navigationContext">The navigation context.</param>
		public void OnNavigatedTo(NavigationContext navigationContext)
		{
			// Not used.
		}

		/// <summary>Called to determine if this instance can handle the navigation request.
		/// </summary>
		/// <param name="navigationContext">The navigation context.</param>
		/// <returns>
		/// <see langword="true" /> if this instance accepts the navigation request; otherwise, <see langword="false" />.
		/// </returns>
		public bool IsNavigationTarget(NavigationContext navigationContext)
		{
			return true;
		}

		/// <summary>Called when the implementer is being navigated away from.
		/// </summary>
		/// <param name="navigationContext">The navigation context.</param>
		public void OnNavigatedFrom(NavigationContext navigationContext)
		{
			// Not used.
		}

		#endregion INavigationAware

		#region Property IpAddress

		/// <summary>The IP address of the buggy.
		/// </summary>
		public string IpAddress
		{
			get
			{
				return mSettings.Settings.IpAddress;
			}
			set
			{
				mSettings.Settings.IpAddress = value;
				mSettings.SaveSettings();
				NotifyPropertyChanged();
			}
		}

		#endregion Property IpAddress

		#region Property Port

		/// <summary>The TCP/IP port used by the buggy.
		/// </summary>
		public int Port
		{
			get { return mSettings.Settings.IpPort; }
			set
			{
				mSettings.Settings.IpPort = value;
				mSettings.SaveSettings();
				NotifyPropertyChanged();
			}
		}

		#endregion Property Port

		#region Property AvailableAnalogSensors

		/// <summary>Gets the available analog sensors.
		/// </summary>
		public IList<string> AvailableAnalogSensors => Enum.GetNames(typeof(AnalogSensor)).ToList();

		#endregion Property AvailableAnalogSensors

		#region Property SelectedSensor

		private AnalogSensor mSelectedSensor = AnalogSensor.All;

		/// <summary>Gets or sets the selected sensor.
		/// </summary>
		public AnalogSensor SelectedSensor
		{
			get { return mSelectedSensor; }
			set
			{
				mSelectedSensor = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Property SelectedSensor

		#region Property SendReadingsContinues

		/// <summary>When set the buggy should continuously send sensor updates.
		/// </summary>
		public bool SendReadingsContinues { get; set; }

		#endregion Property SendReadingsContinues

		#region Property LeftMotorSpeed

		private sbyte mLeftMotorSpeed;

		/// <summary>Gets or sets the left motor speed (in percent).
		/// </summary>
		public sbyte LeftMotorSpeed
		{
			get { return mLeftMotorSpeed; }
			set
			{
				mLeftMotorSpeed = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Property LeftMotorSpeed

		#region Property RightMotorSpeed

		private sbyte mRightMotorSpeed;

		/// <summary>
		/// Gets or sets the right motor speed. (In percent).
		/// </summary>
		public sbyte RightMotorSpeed
		{
			get { return mRightMotorSpeed; }
			set
			{
				mRightMotorSpeed = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Property RightMotorSpeed

		#region Property IsConnected

		/// <summary>Gets a value indicating whether there is connection with the buggy.
		/// </summary>
		public bool IsConnected => mComService.IsConnected;

		#endregion Property IsConnected

		#region Property IsConnecting

		private bool mIsConnecting;

		/// <summary>Gets a value indicating that the client is busy connecting to the buggy.
		/// </summary>
		public bool IsConnecting
		{
			get { return mIsConnecting; }
			private set
			{
				mIsConnecting = value;
				NotifyPropertyChanged();
			}
		}

		#endregion Property IsConnecting

		#region Command ConnectCommand

		/// <summary>Field for the Connect command.
		/// </summary>
		private DelegateCommand mConnectCommand;

		/// <summary>Gets Connect command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand ConnectCommand => mConnectCommand
			// Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
			// is not yet bound to the View, the command is instantiated in a different thread than the
			// main thread. Prevent this by checking on the SynchronizationContext.
			?? (mConnectCommand = System.Threading.SynchronizationContext.Current == null
				? null : new DelegateCommand(Connect, CanConnect));

		/// <summary>Connect to the buggy.
		/// </summary>
		private void Connect()
		{
			IsConnecting = true;
			mComService.Connect(mSettings.Settings.IpAddress, mSettings.Settings.IpPort);
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanConnect()
		{
			return !mComService.IsConnected && !IsConnecting;
		}

		#endregion Command ConnectCommand

		#region Command DisconnectCommand

		/// <summary>Field for the Disconnect command.
		/// </summary>
		private DelegateCommand mDisconnectCommand;

		/// <summary>Gets Disconnect command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand DisconnectCommand => mDisconnectCommand
													// Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
													// is not yet bound to the View, the command is instantiated in a different thread than the
													// main thread. Prevent this by checking on the SynchronizationContext.
													?? (mDisconnectCommand = System.Threading.SynchronizationContext.Current == null
														? null : new DelegateCommand(Disconnect, CanDisconnect));

		/// <summary>Disconnect from the buggy.
		/// </summary>
		private void Disconnect()
		{
			mComService.Disconnect();
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanDisconnect()
		{
			return mComService.IsConnected;
		}

		#endregion Command DisconnectCommand

		#region Command GetVersionCommand

		/// <summary>Field for the GetVersion command.
		/// </summary>
		private DelegateCommand mGetVersionCommand;

		/// <summary>Gets GetVersion command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand GetVersionCommand => mGetVersionCommand
													// Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
													// is not yet bound to the View, the command is instantiated in a different thread than the
													// main thread. Prevent this by checking on the SynchronizationContext.
													?? (mGetVersionCommand = System.Threading.SynchronizationContext.Current == null
														? null : new DelegateCommand(GetVersion, CanGetVersion));

		/// <summary>Get the version of the firmware of the buggy.
		/// </summary>
		private void GetVersion()
		{
			mComService.RequestVersion();
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanGetVersion()
		{
			return mComService.IsConnected;
		}

		#endregion Command GetVersionCommand

		#region Command ResetCommand

		/// <summary>Field for the Reset command.
		/// </summary>
		private DelegateCommand mResetCommand;

		/// <summary>Gets Reset command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand ResetCommand => mResetCommand
											   // Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
											   // is not yet bound to the View, the command is instantiated in a different thread than the
											   // main thread. Prevent this by checking on the SynchronizationContext.
											   ?? (mResetCommand = System.Threading.SynchronizationContext.Current == null
												   ? null : new DelegateCommand(Reset, CanReset));

		/// <summary>Reset the buggy.
		/// </summary>
		private void Reset()
		{
			mComService.Reset();
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanReset()
		{
			return mComService.IsConnected;
		}

		#endregion Command ResetCommand

		#region Command ReadSensorsCommand

		/// <summary>Field for the ReadSensors command.
		/// </summary>
		private DelegateCommand mReadSensorsCommand;

		/// <summary>Gets ReadSensors command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand ReadSensorsCommand => mReadSensorsCommand
													 // Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
													 // is not yet bound to the View, the command is instantiated in a different thread than the
													 // main thread. Prevent this by checking on the SynchronizationContext.
													 ?? (mReadSensorsCommand = System.Threading.SynchronizationContext.Current == null
														 ? null : new DelegateCommand(ReadSensors, CanReadSensors));

		/// <summary>Read the selected sensor(s) of the buggy.
		/// </summary>
		private void ReadSensors()
		{
			mComService.RequestSensors(SelectedSensor, SendReadingsContinues);
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanReadSensors()
		{
			return mComService.IsConnected;
		}

		#endregion Command ReadSensorsCommand

		#region Command SetMotorSpeedsCommand

		/// <summary>Field for the SetMotorSpeeds command.
		/// </summary>
		private DelegateCommand mSetMotorSpeedsCommand;

		/// <summary>Gets SetMotorSpeeds command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand SetMotorSpeedsCommand => mSetMotorSpeedsCommand
														// Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
														// is not yet bound to the View, the command is instantiated in a different thread than the
														// main thread. Prevent this by checking on the SynchronizationContext.
														?? (mSetMotorSpeedsCommand = System.Threading.SynchronizationContext.Current == null
															? null : new DelegateCommand(SetMotorSpeeds, CanSetMotorSpeeds));

		/// <summary>Set the motor speeds.
		/// </summary>
		private void SetMotorSpeeds()
		{
			mComService.SteerMotor(LeftMotorSpeed, RightMotorSpeed);
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanSetMotorSpeeds()
		{
			return mComService.IsConnected;
		}

		#endregion Command SetMotorSpeedsCommand

		#region Command GetErrorCommand

		/// <summary>Field for the GetError command.
		/// </summary>
		private DelegateCommand mGetErrorCommand;

		/// <summary>Gets GetError command.
		/// </summary>
		[System.ComponentModel.Browsable(false)]
		public DelegateCommand GetErrorCommand => mGetErrorCommand
												  // Reflection is used to call ChangeCanExecute on the command. Therefore, when the command
												  // is not yet bound to the View, the command is instantiated in a different thread than the
												  // main thread. Prevent this by checking on the SynchronizationContext.
												  ?? (mGetErrorCommand = System.Threading.SynchronizationContext.Current == null
													  ? null : new DelegateCommand(GetError, CanGetError));

		/// <summary>Get the errors the buggy encountered.
		/// </summary>
		private void GetError()
		{
			mComService.GetError();
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanGetError()
		{
			return mComService.IsConnected;
		}

		#endregion Command GetErrorCommand
	}
}
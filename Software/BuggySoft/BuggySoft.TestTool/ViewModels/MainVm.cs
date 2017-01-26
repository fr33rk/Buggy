using System.Collections.ObjectModel;
using System.Net.Mime;
using System.Windows;
using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Prism;
using Prism.Commands;
using Prism.Regions;

namespace BuggySoft.TestTool.ViewModels
{
	public class MainVm : ViewModelBase, INavigationAware
	{
		private readonly IBuggyCommunicationService mComService;
		private readonly IBuggySoftSettingsService mSettings;

		public MainVm(IBuggyCommunicationService buggyCommunicationService, IBuggySoftSettingsService settingsService)
		{
			mSettings = settingsService;
			mComService = buggyCommunicationService;
			mComService.MessageReceived += ComServiceOnMessageReceived;
			mComService.MessageSend += ComServiceOnMessageSend;	
		}

		public ObservableCollection<MessageVm> Messages { get; } = new ObservableCollection<MessageVm>();

		private void ComServiceOnMessageReceived(object sender, MessageReceivedEventArgs<BaseBuggyMessageWrapper> messageReceivedEventArgs)
		{
			Application.Current.Dispatcher.Invoke(() => Messages.Add(new MessageVm(true, messageReceivedEventArgs.Message)));
		}

		private void ComServiceOnMessageSend(object sender, MessageSendEventArgs messageSendEventArgs)
		{
			Application.Current.Dispatcher.Invoke(() => Messages.Add(new MessageVm(false, messageSendEventArgs.Message)));
		}

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

		/// <summary>
		/// </summary>
		private void Connect()
		{
			mComService.Connect(mSettings.Settings.IpAddress, mSettings.Settings.IpPort);
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanConnect()
		{
			return true;
		}

		#endregion Command ConnectCommand


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

		/// <summary>
		/// </summary>
		private void GetVersion()
		{
			mComService.RequestVersion();
		}

		/// <summary>Determines whether the StartMeasurement command can be executed.
		/// </summary>
		private bool CanGetVersion()
		{
			return true;
		}

		#endregion Command GetVersionCommand				


		public void OnNavigatedTo(NavigationContext navigationContext)
		{
			//throw new NotImplementedException();
		}

		public bool IsNavigationTarget(NavigationContext navigationContext)
		{
			return true;
		}

		public void OnNavigatedFrom(NavigationContext navigationContext)
		{
			//throw new NotImplementedException();
		}

		

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
	}
}
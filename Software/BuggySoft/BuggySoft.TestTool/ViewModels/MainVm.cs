using System.Collections.ObjectModel;
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
		}

		public ObservableCollection<BaseBuggyMessageWrapper> Messages { get; set; } = new ObservableCollection<BaseBuggyMessageWrapper>();

		private void ComServiceOnMessageReceived(object sender, MessageReceivedEventArgs<BaseBuggyMessageWrapper> messageReceivedEventArgs)
		{
			Messages.Add(messageReceivedEventArgs.Message);
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

		#endregion Command ConnectCommand

	}
}
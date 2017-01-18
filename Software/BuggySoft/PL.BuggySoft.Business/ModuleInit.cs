using Microsoft.Practices.Unity;
using PL.BuggySoft.Infrastructure.Services;
using PL.BuggySoft.Infrastructure.Settings;
using PL.Common.Settings;
using PL.Common.Socket;
using PL.Logger;
using Prism.Modularity;

namespace PL.BuggySoft.Business
{
	public class ModuleInit : IModule
	{
		private IUnityContainer mContainer;

		public ModuleInit(IUnityContainer container)
		{
			mContainer = container;
		}

		public void Initialize()
		{
			mContainer.RegisterType<ILogFile, LogFile>("GeneralLog", new ContainerControlledLifetimeManager(),
				new InjectionConstructor("BuggySoft"));

			mContainer.RegisterType<ILogFile, LogFile>("ComLog", new ContainerControlledLifetimeManager(),
				new InjectionConstructor("Communication"));

			mContainer.RegisterType<IFileSystemService, FileSystemService>(new ContainerControlledLifetimeManager());

			mContainer.RegisterType<IBuggySoftSettingsService, BuggySoftSettingsService>(new ContainerControlledLifetimeManager(), new InjectionConstructor(
				mContainer.Resolve<IFileSystemService>(),
				mContainer.Resolve<ILogFile>("ComLog")
				));

			mContainer.RegisterType<ISender, Sender>(new ContainerControlledLifetimeManager());

			var settingsService = mContainer.Resolve<IBuggySoftSettingsService>();
			
			var buggyConnection = new Sender(mContainer.Resolve<ILogFile>("ComLog"), 
				settingsService.Settings.IpAddress, 
				settingsService.Settings.IpPort, 5000);

			mContainer.RegisterType<IBuggyCommunicationService, IBuggyCommunicationService>(
				new ContainerControlledLifetimeManager());
		}
	}
}
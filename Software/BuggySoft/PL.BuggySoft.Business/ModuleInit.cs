using Microsoft.Practices.Unity;
using PL.BuggySoft.Business.Services;
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

			mContainer.Resolve<ILogFile>("GeneralLog").WriteLogStart();

			mContainer.RegisterType<ILogFile, LogFile>("ComLog", new ContainerControlledLifetimeManager(),
				new InjectionConstructor("Communication"));

			mContainer.RegisterType<IFileSystemService, FileSystemService>(new ContainerControlledLifetimeManager());

			mContainer.RegisterType<IBuggySoftSettingsService, BuggySoftSettingsService>(new ContainerControlledLifetimeManager()
			, new InjectionFactory(c => new BuggySoftSettingsService(
				mContainer.Resolve<IFileSystemService>(),
				mContainer.Resolve<ILogFile>("GeneralLog"))
			));

			mContainer.RegisterType<IBuggyCommunicationService, BuggyCommunicationService>(
				new ContainerControlledLifetimeManager()
				, new InjectionFactory(c => new BuggyCommunicationService(mContainer.Resolve<ILogFile>("ComLog")))
			);
		}
	}
}
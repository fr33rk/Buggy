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
				new InjectionConstructor("BuggySoft.log"));

			mContainer.RegisterType<ILogFile, LogFile>("ComLog", new ContainerControlledLifetimeManager(),
				new InjectionConstructor("Communication.log"));

			mContainer.RegisterType<IFileSystemService, FileSystemService>(new ContainerControlledLifetimeManager());

			mContainer.RegisterType<IBuggySoftSettingsService, BuggySoftSettingsService>(new ContainerControlledLifetimeManager());

			mContainer.RegisterType<ISender, Sender>(new ContainerControlledLifetimeManager());
		}
	}
}
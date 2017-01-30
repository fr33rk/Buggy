using Microsoft.Practices.Unity;
using PL.BuggySoft.Business.Services;
using PL.BuggySoft.Infrastructure.Services;
using PL.BuggySoft.Infrastructure.Settings;
using PL.Common.Settings;
using PL.Logger;
using Prism.Modularity;

namespace PL.BuggySoft.Business
{
	/// <summary>Module initialization.
	/// </summary>
	/// <seealso cref="Prism.Modularity.IModule" />
	public class ModuleInit : IModule
	{
		private readonly IUnityContainer mContainer;

		/// <summary>Initializes a new instance of the <see cref="ModuleInit"/> class.
		/// </summary>
		/// <param name="container">The container.</param>
		public ModuleInit(IUnityContainer container)
		{
			mContainer = container;
		}

		/// <summary>Notifies the module that it has be initialized.
		/// </summary>
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
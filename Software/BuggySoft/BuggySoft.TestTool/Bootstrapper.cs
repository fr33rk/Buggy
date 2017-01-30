using System;
using System.Windows;
using PL.Common.Prism;
using PL.Logger;
using Prism.Logging;
using Prism.Modularity;
using Prism.Unity;

namespace BuggySoft.TestTool
{
	/// <summary>Bootstrapper for the BuggySoft.TestTool application.
	/// </summary>
	/// <seealso cref="Prism.Unity.UnityBootstrapper" />
	public class Bootstrapper : UnityBootstrapper
	{
		/// <summary>Initializes the shell.
		/// </summary>
		protected override void InitializeShell()
		{
			base.InitializeShell();

			Application.Current.MainWindow = (Window)Shell;
			Application.Current.MainWindow.Show();
		}

		/// <summary>Creates the shell or main window of the application.
		/// </summary>
		/// <returns>
		/// The shell of the application.
		/// </returns>
		/// <remarks>
		/// If the returned instance is a <see cref="T:System.Windows.DependencyObject" />, the
		/// <see cref="T:Prism.Bootstrapper" /> will attach the default <see cref="T:Prism.Regions.IRegionManager" /> of
		/// the application in its <see cref="F:Prism.Regions.RegionManager.RegionManagerProperty" /> attached property
		/// in order to be able to add regions by using the <see cref="F:Prism.Regions.RegionManager.RegionNameProperty" />
		/// attached property from XAML.
		/// </remarks>
		protected override DependencyObject CreateShell()
		{
			return Container.TryResolve<ShellView>();
		}

		/// <summary>Configures the <see cref="T:Prism.Modularity.IModuleCatalog" /> used by Prism.
		/// </summary>
		protected override void ConfigureModuleCatalog()
		{
			base.ConfigureModuleCatalog();

			AddModuleToCatalog(typeof(PL.BuggySoft.Business.ModuleInit), ModuleCatalog);
			AddModuleToCatalog(typeof(ModuleInit), ModuleCatalog);
		}

		/// <summary>Adds the module to catalog with an unique name (AssemblyQualifiedName).</summary>
		/// <param name="moduleType">Type of the module.</param>
		/// <param name="catalog">The catalog.</param>
		/// Otherwise ModuleInit has to be named differently in each module.
		private void AddModuleToCatalog(Type moduleType, IModuleCatalog catalog)
		{
			var newModuleInfo = new ModuleInfo
			{
				ModuleName = moduleType.AssemblyQualifiedName,
				ModuleType = moduleType.AssemblyQualifiedName,
				InitializationMode = InitializationMode.WhenAvailable
			};
			catalog.AddModule(newModuleInfo);
		}

		/// <summary>Create the <see cref="T:Prism.Logging.ILoggerFacade" /> used by the bootstrapper.
		/// </summary>
		/// <returns></returns>
		/// <remarks>
		/// The base implementation returns a new TextLogger.
		/// </remarks>
		protected override ILoggerFacade CreateLogger()
		{
			var logFile = new LogFile("Prism");
			logFile.WriteLogStart();
			return new PlLoggerFacade(logFile);
		}
	}
}
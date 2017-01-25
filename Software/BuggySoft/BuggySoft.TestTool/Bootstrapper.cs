using System;
using System.Windows;
using PL.Common.Prism;
using PL.Logger;
using Prism.Logging;
using Prism.Modularity;
using Prism.Unity;

namespace BuggySoft.TestTool
{
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

		protected override DependencyObject CreateShell()
		{
			return Container.TryResolve<ShellView>();
		}

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

		protected override ILoggerFacade CreateLogger()
		{
			var logFile = new LogFile("Prism");
			logFile.WriteLogStart();
			return new PlLoggerFacade(logFile);
		}
	}
}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Practices.Prism.Modularity;
using Microsoft.Practices.Prism.UnityExtensions;

namespace PL.BuggySoft.Client.Core
{
    public class Bootstrapper : UnityBootstrapper
    {
	    protected override DependencyObject CreateShell()
	    {
		    return null; //Container.TryResolve<ShellView>();
	    }

	    protected override void ConfigureModuleCatalog()
	    {
		    base.ConfigureModuleCatalog();

			AddModuleToCatalog(typeof(Business.ModuleInit), ModuleCatalog);

	    }

		/// <summary>Adds the module to catalog with an unique name (AssemblyQualifiedName).</summary>
		/// <param name="moduleType">Type of the module.</param>
		/// <param name="catalog">The catalog.</param>
		/// Otherwise ModuleInit has to be named differently in each module.
		private void AddModuleToCatalog(Type moduleType, IModuleCatalog catalog)
		{
			var NewModuleInfo = new ModuleInfo
			{
				ModuleName = moduleType.AssemblyQualifiedName,
				ModuleType = moduleType.AssemblyQualifiedName,
				InitializationMode = InitializationMode.WhenAvailable
			};
			catalog.AddModule(NewModuleInfo);
		}
	}
}

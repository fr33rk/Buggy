using System.Diagnostics;
using BuggySoft.TestTool.Views;
using Microsoft.Practices.Unity;
using PL.BuggySoft.Infrastructure;
using Prism.Modularity;
using Prism.Regions;

namespace BuggySoft.TestTool
{
	public class ModuleInit : IModule
	{
		private IUnityContainer mContainer;
		private IRegionManager mRegionManager;

		public ModuleInit(IUnityContainer container, IRegionManager regionManager)
		{
			mContainer = container;
			mRegionManager = regionManager;
		}

		public void Initialize()
		{
			mContainer.RegisterType<object, MainView>(typeof(MainView).FullName);
			
			mRegionManager.RequestNavigate(RegionNames.MainRegion, typeof(MainView).FullName, 
				result => Debug.WriteLine($"{result.Result}, {result.Error}")
				);			
		}
	}
}
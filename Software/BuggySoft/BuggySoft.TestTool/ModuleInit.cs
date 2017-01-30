using BuggySoft.TestTool.Views;
using Microsoft.Practices.Unity;
using PL.BuggySoft.Infrastructure;
using PL.Logger;
using Prism.Modularity;
using Prism.Regions;

namespace BuggySoft.TestTool
{
	/// <summary>Module initialization.
	/// </summary>
	/// <seealso cref="Prism.Modularity.IModule" />
	public class ModuleInit : IModule
	{
		#region Definitions

		private readonly IUnityContainer mContainer;
		private readonly IRegionManager mRegionManager;

		#endregion Definitions

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="ModuleInit"/> class.
		/// </summary>
		/// <param name="container">The container.</param>
		/// <param name="regionManager">The region manager.</param>
		public ModuleInit(IUnityContainer container, IRegionManager regionManager)
		{
			mContainer = container;
			mRegionManager = regionManager;
		}

		#endregion Constructor(s)

		/// <summary>Notifies the module that it has be initialized.
		/// </summary>
		public void Initialize()
		{
			mContainer.RegisterType<object, MainView>(typeof(MainView).FullName);

			mRegionManager.RequestNavigate(RegionNames.MainRegion, typeof(MainView).FullName,
				result =>
				{
					if (result.Result == false)
						mContainer.Resolve<ILogFile>("GeneralLog").Error(result.Error.ToString());
				});
		}
	}
}
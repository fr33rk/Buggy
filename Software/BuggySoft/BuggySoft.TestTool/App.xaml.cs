using System.Linq;
using System.Windows;
using PL.Logger;

namespace BuggySoft.TestTool
{
	/// <summary>
	/// Interaction logic for App.xaml
	/// </summary>
	public partial class App
	{
		private static Bootstrapper mBootstrapper;

		protected override void OnStartup(StartupEventArgs e)
		{
			StartInstance(e);
		}

		private static void StartInstance(StartupEventArgs e)
		{
			// Set the current user interface culture to the specific culture Russian
			System.Threading.Thread.CurrentThread.CurrentUICulture =
				new System.Globalization.CultureInfo("en");

			// Configure Bootstrapper
			mBootstrapper = new Bootstrapper();
			mBootstrapper.Run();
		}

		protected override void OnExit(ExitEventArgs e)
		{
			var logFiles = mBootstrapper.Container.ResolveAll(typeof(ILogFile)).OfType<ILogFile>();

			foreach (var logFile in logFiles)
			{
				logFile.WriteLogEnd();
			}
		}
	}
}
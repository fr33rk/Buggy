using System.Linq;
using System.Windows;
using PL.Logger;

namespace BuggySoft.TestTool
{
	/// <summary>Interaction logic for App.xaml
	/// </summary>
	public partial class App
	{
		private static Bootstrapper mBootstrapper;

		/// <summary>Raises the <see cref="E:System.Windows.Application.Startup" /> event.
		/// </summary>
		/// <param name="e">A <see cref="T:System.Windows.StartupEventArgs" /> that contains the event data.</param>
		protected override void OnStartup(StartupEventArgs e)
		{
			StartInstance();
		}

		private static void StartInstance()
		{
			// Set the current user interface culture to the specific culture Russian
			System.Threading.Thread.CurrentThread.CurrentUICulture =
				new System.Globalization.CultureInfo("en");

			// Configure Bootstrapper
			mBootstrapper = new Bootstrapper();
			mBootstrapper.Run();
		}

		/// <summary>Raises the <see cref="E:System.Windows.Application.Exit" /> event.
		/// </summary>
		/// <param name="e">An <see cref="T:System.Windows.ExitEventArgs" /> that contains the event data.</param>
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
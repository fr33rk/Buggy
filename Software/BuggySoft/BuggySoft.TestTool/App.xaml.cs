using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Microsoft.Practices.Unity;
using PL.Logger;

namespace BuggySoft.TestTool
{
	/// <summary>
	/// Interaction logic for App.xaml
	/// </summary>
	public partial class App : Application
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

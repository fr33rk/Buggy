﻿using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace BuggySoft.TestTool
{
	/// <summary>
	/// Interaction logic for App.xaml
	/// </summary>
	public partial class App : Application
	{
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
			var bootstrapper = new Bootstrapper();
			bootstrapper.Run();
		}
	}
}

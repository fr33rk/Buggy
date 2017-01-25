using System.Windows.Controls;
using BuggySoft.TestTool.ViewModels;

namespace BuggySoft.TestTool.Views
{
	/// <summary>
	/// Interaction logic for MainView.xaml
	/// </summary>
	public partial class MainView
	{
		public MainView(MainVm mainVm)
		{
			InitializeComponent();
			DataContext = mainVm;
		}
	}
}
using BuggySoft.TestTool.ViewModels;

namespace BuggySoft.TestTool.Views
{
	/// <summary>
	/// Interaction logic for MainView.xaml
	/// </summary>
	public partial class MainView
	{
		/// <summary>Initializes a new instance of the <see cref="MainView"/> class.
		/// </summary>
		/// <param name="mainVm">The view model which is the data source of this view..</param>
		public MainView(MainVm mainVm)
		{
			InitializeComponent();
			DataContext = mainVm;
		}
	}
}
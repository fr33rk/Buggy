using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Settings;
using PL.Logger;

namespace PL.BuggySoft.Infrastructure.Settings
{
	/// <summary>Settings service provides access to the settings for BuggySoft and is able to load and save them.
	/// </summary>
	public class BuggySoftSettingsService : BaseSettingsService<BuggySoftSettings>, IBuggySoftSettingsService
	{
		/// <summary>Initializes a new instance of the <see cref="BuggySoftSettingsService"/> class.
		/// </summary>
		/// <param name="fileService">The file service to save and load settings.</param>
		/// <param name="logger">The logger.</param>
		public BuggySoftSettingsService(IFileSystemService fileService, ILogFile logger)
			: base(fileService, logger)
		{
			// Nothing additional to do here.
		}
	}
}
using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Settings;
using PL.Logger;

namespace PL.BuggySoft.Infrastructure.Settings
{
	public class BuggySoftSettingsService : BaseSettingsService<BuggySoftSettings>, IBuggySoftSettingsService
	{
		public BuggySoftSettingsService(IFileSystemService fileService, ILogFile logger)
			: base(fileService, logger)
		{
			// Nothing additional to do here.
		}
	}
}
using PL.BuggySoft.Infrastructure.Settings;
using PL.Common.Settings;

namespace PL.BuggySoft.Infrastructure.Services
{
	public interface IBuggySoftSettingsService : ISettingsService
	{
		BuggySoftSettings Settings { get; set; }
	}
}
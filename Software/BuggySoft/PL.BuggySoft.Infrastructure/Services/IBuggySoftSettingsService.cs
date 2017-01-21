using PL.BuggySoft.Infrastructure.Settings;
using PL.Common.Settings;

namespace PL.BuggySoft.Infrastructure.Services
{
	/// <summary>Settings service.
	/// 
	/// </summary>
	/// <seealso cref="PL.Common.Settings.ISettingsService" />
	public interface IBuggySoftSettingsService : ISettingsService
	{
		/// <summary>Gets or sets the settings.
		/// </summary>
		BuggySoftSettings Settings { get; set; }
	}
}
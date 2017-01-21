using System.ComponentModel;

namespace PL.BuggySoft.Infrastructure.Settings
{
	/// <summary>Settings for the buggy soft application(s).
	/// </summary>
	public class BuggySoftSettings
	{
		/// <summary>The IP address of the buggy.
		/// </summary>
		[DefaultValue("192.168.5.21")]
		public string IpAddress { get; set; }

		/// <summary>The IP port of the buggy.
		/// </summary>
		[DefaultValue(6060)]
		public int IpPort { get; set; }
	}
}
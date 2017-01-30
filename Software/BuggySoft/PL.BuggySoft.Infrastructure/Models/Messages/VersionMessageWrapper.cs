using System;
using System.Diagnostics.CodeAnalysis;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the version result message.
	/// </summary>
	public class VersionMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="VersionMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		[ExcludeFromCodeCoverage]
		public VersionMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
		}

		/// <summary>Gets the version.</summary>
		public Version Version => new Version(Data[0], Data[1], Data[2]);

		/// <summary>Specifics the data string.</summary>
		/// <returns></returns>
		public override string SpecificDataString()
		{
			return $"Version: {Version}";
		}
	}
}
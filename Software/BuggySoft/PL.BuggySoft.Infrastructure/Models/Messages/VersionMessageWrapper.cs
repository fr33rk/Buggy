using System;
using System.Diagnostics.CodeAnalysis;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the version result message.
	/// </summary>
	public class VersionMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="VersionMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		[ExcludeFromCodeCoverage]
		public VersionMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
		}

		/// <summary>Initializes a new instance of the <see cref="VersionMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		/// <param name="major">The major version number.</param>
		/// <param name="minor">The minor version number.</param>
		/// <param name="build">The build version number.</param>
		public VersionMessageWrapper(ushort taskId, byte major, byte minor, byte build)
			: base(BuggyCommand.Version, false, taskId, 3)
		{
			Data[0] = major;
			Data[1] = minor;
			Data[2] = build;
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
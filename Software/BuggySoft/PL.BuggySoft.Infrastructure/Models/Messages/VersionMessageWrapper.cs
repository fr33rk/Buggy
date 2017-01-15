using System;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public class VersionMessageWrapper : BaseBuggyMessageWrapper
	{
		public VersionMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
			
		}

		public Version Version => new Version(Data[0], Data[1], Data[2]);

		public override string SpecificDataString()
		{
			return $", Version: {Version}";
		}
	}
}
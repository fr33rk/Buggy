using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public static class BuggyMessageFactory
	{
		public static BaseBuggyMessageWrapper CreateWrapperForRawMessage(byte[] rawMessage)
		{
			var baseMessage = new BaseBuggyMessageWrapper(rawMessage);

			switch (baseMessage.Command)
			{
				case BuggyCommand.Version:
					return new VersionMessageWrapper(rawMessage);
				case BuggyCommand.ResetDone:
					return new ResetDoneMessageWrapper(rawMessage);
				case BuggyCommand.SensorResult:
					return new SensorResultMessageWrapper(rawMessage);
				case BuggyCommand.SteerMotorDone:
				default:
					return baseMessage;
			}
		}
	}
}

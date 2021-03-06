﻿namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Factory class to create the correct message wrapper from a message send by the buggy.
	/// </summary>
	public static class BuggyMessageFactory
	{
		/// <summary>Creates the wrapper for raw message.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		/// <returns>The correct message wrapper.</returns>
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
					if (baseMessage.DataSize == 3)
					{
						return new SensorResultMessageWrapper(rawMessage);
					}
					return new SensorResultAllMessageWrapper(rawMessage);
				case BuggyCommand.SteerMotorDone:
					return new SteerMotorDoneMessageWrapper(rawMessage);
				default:
					return baseMessage;
			}
		}
	}
}
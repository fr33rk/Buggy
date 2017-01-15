using System;
using System.Linq;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public class BaseBuggyMessageWrapper
	{
		public BaseBuggyMessageWrapper(BuggyCommand command, bool isRtr, ushort taskId, bool isError, byte dataSize)
			: this()
		{
			Command = command;
			IsRtr = isRtr;
			TaskId = taskId;
			IsError = isError;
			DataSize = dataSize;
		}

		public BaseBuggyMessageWrapper()
		{
			Data = new byte[11];
		}

		public BaseBuggyMessageWrapper(byte[] rawMessage)
		{
			FromBuffer(rawMessage);
		}

		public BuggyCommand Command { get; private set; }
		public bool IsRtr { get; private set; }
		public ushort TaskId { get; private set; }
		public bool IsError { get; private set; }
		public byte DataSize { get; private set; }
		public byte[] Data { get; private set; }

		public byte[] ToRawMessage()
		{
			var retValue = new byte[15];

			retValue[0] = (byte)((byte)Command << 1 | (IsRtr ? 0x01 : 0x00));
			Array.Copy(BitConverter.GetBytes(TaskId), 0, retValue, 1, 2);
			retValue[3] = (byte)(DataSize << 1 | (IsError ? 0x01 : 0x00));
			Array.Copy(Data, 0, retValue, 4, 11);

			return retValue;
		}

		public void FromBuffer(byte[] raw)
		{
			Command = (BuggyCommand)(raw[0] >> 1);
			IsRtr = (raw[0] & 0x01) == 0x01;
			TaskId = (ushort)((raw[1] << 8) | (raw[2]));
			IsError = (raw[3] & 0x01) == 0x01;
			DataSize = (byte)((raw[3] >> 1) & 0x03);
			Data = raw.Skip(4).Take(11).ToArray();
		}

		public override string ToString()
		{
			var hexData = Array.ConvertAll(Data.Take(DataSize).ToArray(), input => input.ToString("X2")).ToArray();
			return $"Task ID: {TaskId}, Command: {Command}, RTR: {IsRtr}, Error: {IsError}, Size: {DataSize}, Data: [{string.Join(",", hexData)}]{SpecificDataString()}";
			//return $"Task ID: {TaskId}, Command: {Command}, RTR: {IsRtr}, Error: {IsError}, Size: {DataSize}, Data: [{string.Join(",", Data.Take(DataSize))}]{SpecificDataString()}";
		}

		public virtual string SpecificDataString()
		{
			return "";
		}
	}
}
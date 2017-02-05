using System;
using System.Linq;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Basic wrapper around the messages used to communicate with the buggy.
	/// Layout:
	/// 0123456789012345678901234567890123456789012345678901234567890123...
	/// [Command]|[     Task ID      ][n/u]+--++[         Data          ..]
	///        [RTR]                         | [IsError]
	///                                    [Data size]
	/// </summary>
	public class BaseBuggyMessageWrapper
	{
		#region Constructor(s)

		/// <summary>
		/// Initializes a new instance of the <see cref="BaseBuggyMessageWrapper"/> class.
		/// </summary>
		/// <param name="command">The command.</param>
		/// <param name="isRtr">Request for data.</param>
		/// <param name="taskId">The task identifier.</param>
		/// <param name="dataSize">Size of the data.</param>
		public BaseBuggyMessageWrapper(BuggyCommand command, bool isRtr, ushort taskId, byte dataSize)
			: this()
		{
			Command = command;
			IsRtr = isRtr;
			TaskId = taskId;
			DataSize = dataSize;
		}

		/// <summary>Initializes a new instance of the <see cref="BaseBuggyMessageWrapper"/> class.
		/// </summary>
		public BaseBuggyMessageWrapper()
		{
			Data = new byte[11];
		}

		/// <summary>Initializes a new instance of the <see cref="BaseBuggyMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		public BaseBuggyMessageWrapper(byte[] rawMessage)
		{
			FromBuffer(rawMessage);
		}

		#endregion Constructor(s)

		#region Properties

		/// <summary>Gets the command.</summary>
		public BuggyCommand Command { get; private set; }

		/// <summary>Gets a value indicating whether the message is a request for data..</summary>
		public bool IsRtr { get; private set; }

		/// <summary>Gets the task identifier.</summary>
		public ushort TaskId { get; private set; }

		/// <summary>Gets a value indicating whether an error occured.</summary>
		public bool IsError { get; private set; }

		/// <summary>Gets the size of the data.</summary>
		public byte DataSize { get; private set; }

		/// <summary>Gets the data.</summary>
		public byte[] Data { get; private set; }

		#endregion Properties

		/// <summary>Gets the raw message.</summary>
		public byte[] ToRawMessage()
		{
			var retValue = new byte[15];

			retValue[0] = (byte)((byte)Command << 1 | (IsRtr ? 0x01 : 0x00));
			Array.Copy(BitConverter.GetBytes(TaskId), 0, retValue, 1, 2);
			retValue[3] = (byte)(DataSize << 1 | (IsError ? 0x01 : 0x00));
			Array.Copy(Data, 0, retValue, 4, 11);

			return retValue;
		}

		/// <summary>Get the message properties from a raw message.</summary>
		/// <param name="raw">The raw message.</param>
		private void FromBuffer(byte[] raw)
		{
			Command = (BuggyCommand)(raw[0] >> 1);
			IsRtr = (raw[0] & 0x01) == 0x01;
			// Task ID is 16 bits and is swapped by firmware.
			TaskId = (ushort)((raw[2] << 8) | (raw[1]));
			IsError = (raw[3] & 0x01) == 0x01;
			DataSize = (byte)((raw[3] >> 1) & 0x0F);
			Data = raw.Skip(4).Take(11).ToArray();
		}

		/// <summary>Returns a <see cref="System.String" /> that represents this instance.
		/// </summary>
		/// <returns>A <see cref="System.String" /> that represents this instance.</returns>
		public override string ToString()
		{
			var hexData = Array.ConvertAll(Data.Take(DataSize).ToArray(), input => input.ToString("X2")).ToArray();
			var retValue = $"Task ID: {TaskId}, Command: {Command}, RTR: {IsRtr}, Error: {IsError}, Size: {DataSize}, Data: [{string.Join(",", hexData)}]";

			var specficString = SpecificDataString();
			if (specficString.Length > 0)
			{
				retValue += $", {specficString}";
			}

			return retValue;
		}

		/// <summary>Specific string for the data.</summary>
		/// <returns></returns>
		public virtual string SpecificDataString()
		{
			return "";
		}
	}
}
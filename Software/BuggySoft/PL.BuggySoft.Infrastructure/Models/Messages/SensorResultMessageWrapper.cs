using System;
using System.Diagnostics.CodeAnalysis;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the sensor result message.
	/// </summary>
	public class SensorResultMessageWrapper : BaseBuggyMessageWrapper
	{
		#region Constructor(s)

		/// <summary>
		/// Initializes a new instance of the <see cref="SensorResultMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		[ExcludeFromCodeCoverage]
		public SensorResultMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
			ConvertData();
		}

		#endregion Constructor(s)

		/// <summary>Gets the single result, filled in case only one sensor was requested.</summary>
		/// <value>The single result.</value>
		public ushort SingleResult { get; private set; }

		/// <summary>Gets the value of the right distance sensor.</summary>
		public ushort DistanceRight { get; private set; }

		/// <summary>Gets the value of the frontal distance sensor.</summary>
		public ushort DistanceFront { get; private set; }

		/// <summary>Gets the value of the left distance sensor.</summary>
		public ushort DistanceLeft { get; private set; }

		/// <summary>Gets the value of the left line sensor.</summary>
		public bool LineSensorRight { get; private set; }

		/// <summary>Gets the value of the right line sensor.</summary>
		public bool LineSensorLeft { get; private set; }

		/// <summary>Gets the value of the microphone.</summary>
		public ushort Microphone { get; private set; }

		/// <summary>Gets the value of the light sensor.</summary>
		public ushort Light { get; private set; }

		private void ConvertData()
		{
			if (DataSize == 2)
			{
				SingleResult = BitConverter.ToUInt16(Data, 0);
			}
			else
			{
				DistanceLeft = BitConverter.ToUInt16(Data, 0);
				DistanceFront = BitConverter.ToUInt16(Data, 2);
				DistanceRight = BitConverter.ToUInt16(Data, 4);
				Light = BitConverter.ToUInt16(Data, 6);
				Microphone = BitConverter.ToUInt16(Data, 8);
				LineSensorLeft = (Data[10] & 0x01) == 0x01;
				LineSensorRight = (Data[10] & 0x02) == 0x02;
			}
		}
	}
}
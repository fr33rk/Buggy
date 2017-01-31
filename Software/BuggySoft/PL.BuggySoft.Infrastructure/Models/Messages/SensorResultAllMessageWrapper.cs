using System;
using System.Diagnostics.CodeAnalysis;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the sensor result message.
	/// </summary>
	public class SensorResultAllMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="SensorResultAllMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		[ExcludeFromCodeCoverage]
		public SensorResultAllMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
			ConvertData();
		}

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
			DistanceLeft = BitConverter.ToUInt16(Data, 0);
			DistanceFront = BitConverter.ToUInt16(Data, 2);
			DistanceRight = BitConverter.ToUInt16(Data, 4);
			Light = BitConverter.ToUInt16(Data, 6);
			Microphone = BitConverter.ToUInt16(Data, 8);
			LineSensorLeft = (Data[10] & 0x01) == 0x01;
			LineSensorRight = (Data[10] & 0x02) == 0x02;
		}

		/// <summary>Specifics the data string.</summary>
		/// <returns></returns>
		public override string SpecificDataString()
		{
			return $"Left:{DistanceLeft} Front:{DistanceFront} Right:{DistanceRight} Line-left:{(LineSensorLeft ? "yes" : "no")} Line-right:{(LineSensorRight ? "yes" : "no")} Light: {Light} Mic: {Microphone}";
		}
	}
}
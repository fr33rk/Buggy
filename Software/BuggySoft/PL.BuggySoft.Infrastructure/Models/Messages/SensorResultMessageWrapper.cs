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

		/// <summary>The sensor that has been read.</summary>
		/// <value>The sensor.</value>
		public AnalogSensor Sensor { get; private set; }

		/// <summary>Gets the single result, filled in case only one sensor was requested.</summary>
		/// <value>The single result.</value>
		public ushort Result { get; private set; }

		private void ConvertData()
		{
			Sensor = (AnalogSensor)Data[0];
			Result = BitConverter.ToUInt16(Data, 1);
		}

		/// <summary>Specific string for the data.</summary>
		/// <returns></returns>
		public override string SpecificDataString()
		{
			return $"Sensor:{Sensor} Result:{Result}";
		}
	}
}
using System;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the sensor request message.
	///
	/// </summary>
	public class SensorRequestMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="SensorRequestMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		/// <param name="sensor">The sensor.</param>
		/// <param name="continues">True, when the buggy should automatically send updates at a set interval.</param>
		public SensorRequestMessageWrapper(ushort taskId, AnalogSensor sensor, bool continues)
			: base(BuggyCommand.SensorReq, false, taskId, 2)
		{
			Data[0] = (byte)sensor;
			Data[1] = Convert.ToByte(continues);
		}
	}
}
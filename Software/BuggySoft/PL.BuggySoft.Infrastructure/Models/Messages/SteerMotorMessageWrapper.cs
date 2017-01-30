namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Message wrapper for the message that commands the
	///
	/// </summary>
	public class SteerMotorMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="SteerMotorMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		/// <param name="leftMotorSpeed">The left motor speed. Negative when motor should run in reverse.</param>
		/// <param name="rightMotorSpeed">The right motor speed. Negative when motor should run in reverse.</param>
		public SteerMotorMessageWrapper(ushort taskId, sbyte leftMotorSpeed, sbyte rightMotorSpeed)
			: base(BuggyCommand.SteerMotor, false, taskId, 2)
		{
			Data[0] = (byte)leftMotorSpeed;
			Data[1] = (byte)rightMotorSpeed;
		}

		/// <summary>Specific string for the data.</summary>
		/// <returns></returns>
		public override string SpecificDataString()
		{
			return $"Left: {(sbyte)Data[0]}, Right: {(sbyte)Data[1]}";
		}
	}
}
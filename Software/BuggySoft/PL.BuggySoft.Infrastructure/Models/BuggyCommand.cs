namespace PL.BuggySoft.Infrastructure.Models
{
	/// <summary>Commands issued to and send by the buggy.
	/// 
	/// </summary>
	public enum BuggyCommand
	{
#pragma warning disable 1591
		Unknown = 0x00,
		VersionReq = 0x02,
		Version = 0x03,
		Reset = 0x04,
		ResetDone = 0x05,
		SensorReq = 0x06,
		SensorResult = 0x07,
		SteerMotor = 0x08,
		SteerMotorDone = 0x09,
		SendError = 0x0A
#pragma warning restore 1591
	}
}
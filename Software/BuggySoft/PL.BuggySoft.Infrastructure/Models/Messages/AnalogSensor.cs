namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Analog sensors available on the buggy.
	/// </summary>
	public enum AnalogSensor
	{
#pragma warning disable 1591
		DistanceLeft = 0,
		DistanceFront,
		DistanceRight,
		Microphone,
		Light,
		All = 0xFF
#pragma warning restore 1591
	}
}
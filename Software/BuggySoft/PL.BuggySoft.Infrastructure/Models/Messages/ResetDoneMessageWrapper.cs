using System;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper for the ResetDone message.
	/// </summary>
	public class ResetDoneMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>
		/// Reasons why the buggy has reset.
		/// </summary>
		[Flags]
		public enum BuggyResetReason
		{
#pragma warning disable 1591
			BrownOutReset = 0x01,
			PowerOnReset = 0x02,
			PowerDownDetection = 0x04,
			WatchDogTimeOut = 0x08,
			ResetInstruction = 0x10,

			StackUnderflow = 0x40,
			StackFull = 0x80
#pragma warning restore 1591
		}

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="ResetDoneMessageWrapper"/> class.
		/// </summary>
		/// <param name="rawMessage">The raw message.</param>
		public ResetDoneMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
		}

		#endregion Constructor(s)

		/// <summary>Gets the reason(s) why the buggy reset.</summary>
		public BuggyResetReason Reason => (BuggyResetReason)Data[0];

		/// <summary>Specifics the data string.</summary>
		/// <returns></returns>
		public override string SpecificDataString()
		{
			return $", Reset reason(s): {Reason}";
		}
	}
}
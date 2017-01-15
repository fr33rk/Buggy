using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public class ResetDoneMessageWrapper : BaseBuggyMessageWrapper
	{
		[Flags]
		public enum BuggyResetReason
		{
			BrownOutReset = 0x01,
			PowerOnReset = 0x02,
			PowerDownDetection = 0x04,
			WatchDogTimeOut = 0x08,
			ResetInstruction = 0x10,

			StackUnderflow = 0x40,
			StackFull = 0x80
		}

		
		public ResetDoneMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
		{
			
		}

		public BuggyResetReason Reason => (BuggyResetReason) Data[0];

		public override string SpecificDataString()
		{
			return $", Reset reason(s): {Reason}";
		}
	}
}

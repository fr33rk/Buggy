using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
    public class SteerMotorDoneMessageWrapper : BaseBuggyMessageWrapper
    {
	    public SteerMotorDoneMessageWrapper(byte[] rawMessage)
			: base(rawMessage)
	    {
		    
	    }

	    public SteerMotorDoneMessageWrapper(ushort taskId)
			: base(BuggyCommand.SteerMotorDone, false, taskId, 0)
	    {
		    
	    }
    }
}

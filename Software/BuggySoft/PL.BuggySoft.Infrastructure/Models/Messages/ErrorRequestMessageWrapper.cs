using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public class ErrorRequestMessageWrapper : BaseBuggyMessageWrapper
	{
		public ErrorRequestMessageWrapper(ushort taskId)
			: base(BuggyCommand.SendError, true, taskId, 0)
		{
		}
	}
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PL.BuggySoft.Infrastructure.Models;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace BuggySoft.TestTool.ViewModels
{
    public class MessageVm
    {
	    private readonly BaseBuggyMessageWrapper mWrappedMessage;
	    private readonly bool mWasReceieved;

	    public MessageVm(bool wasReceieved, BaseBuggyMessageWrapper wrappedMessage)
	    {
		    mWrappedMessage = wrappedMessage;
		    mWasReceieved = wasReceieved;
	    }

	    public string Direction => mWasReceieved ? "<" : ":";

	    public BuggyCommand Command => mWrappedMessage.Command;

	    public string Rtr => mWrappedMessage.IsRtr ? "Yes" : "No";

	    public int TaskId => mWrappedMessage.TaskId;

	    public string Error => mWrappedMessage.IsError ? "Yes" : "No";

	    public int DataSize => mWrappedMessage.DataSize;

	    public string Data => mWrappedMessage.ToString();
    }
}

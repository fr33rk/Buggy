namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	public class VersionRequestMessageWrapper : BaseBuggyMessageWrapper
	{
		public VersionRequestMessageWrapper(ushort taskId)
			: base(BuggyCommand.VersionReq, true, taskId, false, 0)
		{
		}
	}
}
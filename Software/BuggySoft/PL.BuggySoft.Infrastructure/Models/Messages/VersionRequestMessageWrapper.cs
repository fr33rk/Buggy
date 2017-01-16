namespace PL.BuggySoft.Infrastructure.Models.Messages
{
	/// <summary>Wrapper around the version request message.
	/// </summary>
	public class VersionRequestMessageWrapper : BaseBuggyMessageWrapper
	{
		/// <summary>Initializes a new instance of the <see cref="VersionRequestMessageWrapper"/> class.
		/// </summary>
		/// <param name="taskId">The task identifier.</param>
		public VersionRequestMessageWrapper(ushort taskId)
			: base(BuggyCommand.VersionReq, true, taskId, 0)
		{
		}
	}
}
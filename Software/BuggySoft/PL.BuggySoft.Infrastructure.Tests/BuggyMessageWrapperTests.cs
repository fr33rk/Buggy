using System;
using System.Linq;
using NUnit.Framework;
using PL.BuggySoft.Infrastructure.Models;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace PL.BuggySoft.Infrastructure.Tests
{
	[TestFixture]
	public class BuggyMessageWrapperTests
	{
		[Test]
		public void BuggyMessage_BasePropertiesFromBuffer_CorrectConversion()
		{
			// Arrange
			var rawData = new byte[] { 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			// Act
			var unitUnderTest = new BaseBuggyMessageWrapper(rawData);

			// Assert
			Assert.AreEqual(BuggyCommand.VersionReq, unitUnderTest.Command);
			Assert.AreEqual(true, unitUnderTest.IsRtr, "IsRtr");
			Assert.AreEqual(1, unitUnderTest.TaskId, "TaskId");
			Assert.AreEqual(false, unitUnderTest.IsError, "IsError");
			Assert.AreEqual(0, unitUnderTest.DataSize, "Data size");
		}

		[Test]
		public void BuggyMessage_DataPropertiesFromBuffer_CorrectConversion()
		{
			// Arrange
			var rawData = new byte[] { 0x06, 0x01, 0x00, 0x07, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			// Act
			var unitUnderTest = new BaseBuggyMessageWrapper(rawData);

			// Assert
			Assert.AreEqual(BuggyCommand.Version, unitUnderTest.Command);
			Assert.AreEqual(false, unitUnderTest.IsRtr, "IsRtr");
			Assert.AreEqual(256, unitUnderTest.TaskId, "TaskId");
			Assert.AreEqual(true, unitUnderTest.IsError, "IsError");
			Assert.AreEqual(3, unitUnderTest.DataSize, "Data size");
			Assert.That(unitUnderTest.Data.Take(3).ToArray(), Is.EquivalentTo(new byte[] { 1, 2, 3 }));
		}

		[Test]
		public void BuggyMessage_BasePropertiesToBuffer_CorrectBuffer()
		{
			// Arrange
			var unitUnderTest = new BaseBuggyMessageWrapper(BuggyCommand.VersionReq, true, 21, 0);

			// Assert
			Assert.That(unitUnderTest.ToRawMessage(), Is.EquivalentTo(new byte[] { 0x05, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }));
		}

		[Test]
		public void BuggyMessage_DataPropertiesToBuffer_CorrectBuffer()
		{
			// Arrange
			var rawMessage = new byte[]
				{0x06, 0x00, 0x15, 0x07, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			var unitUnderTest = new BaseBuggyMessageWrapper(rawMessage);

			// Assert
			Assert.That(unitUnderTest.ToRawMessage(), Is.EquivalentTo(rawMessage));
		}

		[Test]
		public void BuggyMessage_BasePropertiesTostring()
		{
			// Arrange
			var unitUnderTest = new BaseBuggyMessageWrapper(BuggyCommand.VersionReq, true, 2109, 0);

			// Assert
			Assert.That(unitUnderTest.ToString(), Is.EqualTo("Task ID: 2109, Command: VersionReq, RTR: True, Error: False, Size: 0, Data: []"));
		}

		#region Version

		[Test]
		public void VersionBuggyMessage_FromBuffer_CorrectVersion()
		{
			// Arrange
			var expectedVersion = new Version(1, 2, 3);
			var unitUnderTest = new VersionMessageWrapper(new byte[]
					{0x06, 0x00, 0x15, 0x07, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});

			// Assert
			Assert.That(unitUnderTest.Version, Is.EqualTo(expectedVersion));
		}

		#endregion Version

		#region Reset

		[Test]
		public void ResetBuggyMessage_FromBuffer_CorrectReasons()
		{
			// Arrange
			var expectedReasons = ResetDoneMessageWrapper.BuggyResetReason.PowerOnReset |
			                      ResetDoneMessageWrapper.BuggyResetReason.ResetInstruction;
			var unitUnderTest = new ResetDoneMessageWrapper(new byte[]
					{0x06, 0x00, 0x15, 0x02, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});

			// Assert
			Assert.That(unitUnderTest.Reason, Is.EqualTo(expectedReasons));
		}

		[Test]
		public void ResetBuggyMessage_FromBuffer_CorrectString()
		{
			// Arrange
			var unitUnderTest = new ResetDoneMessageWrapper(new byte[]
					{0x0A, 0x00, 0x15, 0x02, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});

			// Assert
			Assert.That(unitUnderTest.ToString(), Is.EqualTo("Task ID: 21, Command: ResetDone, RTR: False, Error: False, Size: 1, Data: [12], Reset reason(s): PowerOnReset, ResetInstruction"));
		}

		#endregion
	}
}
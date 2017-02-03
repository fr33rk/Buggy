using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NUnit.Framework;
using PL.BuggySoft.Infrastructure.Models.Messages;

namespace PL.BuggySoft.Infrastructure.Tests
{
	[TestFixture]
	public class BuggyMessageFactoryTests
	{
		[Test]
		public void BuggyMessageFactory_ReceivedVersionResultMsg_CreatedVersionMessageWrapper()
		{
			// Arrange
			var rawMessage = new VersionMessageWrapper(1, 1, 2, 3).ToRawMessage();

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper is VersionMessageWrapper);
		}

		[Test]
		public void BuggyMessageFactory_ReceivedResetDonwMsg_CreatedResetDoneMessageWrapper()
		{
			// Arrange
			var rawMessage = new ResetDoneMessageWrapper(1, ResetDoneMessageWrapper.BuggyResetReason.PowerOnReset).ToRawMessage();

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper is ResetDoneMessageWrapper);
		}

		[Test]
		public void BuggyMessageFactory_ReceivedSingleSensorResultMsg_CreatesSensorResultsMessageWrapper()
		{
			// Arrange
			var rawMessage = new byte[] {0x0E, 0x01, 0x00, 0x06, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper is SensorResultMessageWrapper);
		}

		[Test]
		public void BuggyMessageFactory_ReceivedAllSensorResultMsg_CreatedSensorResultsAllMessageWrapper()
		{
			// Arrange
			var rawMessage = new byte[] { 0x0E, 0x01, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper is SensorResultAllMessageWrapper);
		}

		[Test]
		public void BuggyMessageFactory_ReceivedSteerMotorDoneMgs_CreatedSteerMotorDoneMessageWrapper()
		{
			// Arrange
			var rawMessage = new SteerMotorDoneMessageWrapper(1).ToRawMessage();

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper is SteerMotorDoneMessageWrapper);
		}

		[Test]
		public void BuggyMessageFactory_ReceivedUnknownMgs_CreatedBaseMessageWrapper()
		{
			// Arrange
			var rawMessage = new byte[] { 0xFF, 0xFF, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

			// Act
			var actualMessageWrapper = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			// Assert
			Assert.That(actualMessageWrapper != null);
		}
	}
}

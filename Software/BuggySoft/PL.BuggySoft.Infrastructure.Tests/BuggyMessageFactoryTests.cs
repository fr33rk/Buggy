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

    }
}

/*
   Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.

   This file is licensed under the Apache License, Version 2.0 (the "License").
   You may not use this file except in compliance with the License. A copy of
   the License is located at

    http://aws.amazon.com/apache2.0/

   This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied. See the License for the
   specific language governing permissions and limitations under the License.
*/
#include <aws/core/Aws.h>

#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/CreateQueueRequest.h>
#include <aws/sqs/model/CreateQueueResult.h>

#include <iostream>

/**
 * Creates a long-polled sqs queue based on command line input
 */
int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: sqs_long_polling_on_create_queue <queue_name> <long_poll_time_in_seconds>" << std::endl;
        return 1;
    }

    Aws::String queueName = argv[1];
    Aws::String longPollTimeInSeconds = argv[2];

    Aws::SDKOptions options;
    Aws::InitAPI(options);

    Aws::SQS::SQSClient sqs_client;

    Aws::SQS::Model::CreateQueueRequest createQueueRequest;
    createQueueRequest.SetQueueName(queueName);
    createQueueRequest.AddAttributes(Aws::SQS::Model::QueueAttributeName::ReceiveMessageWaitTimeSeconds, longPollTimeInSeconds);
    auto createQueueOutcome = sqs_client.CreateQueue(createQueueRequest);
    if(createQueueOutcome.IsSuccess())
    {
        std::cout << "Successfully created long-polled queue " << queueName << std::endl;
    }
    else
    {
        std::cout << "Error creating long-polled queue " << queueName << ": " << createQueueOutcome.GetError().GetMessage() << std::endl;
    }

    Aws::ShutdownAPI(options);

    return 0;
}




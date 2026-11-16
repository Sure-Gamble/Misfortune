#include "command.h"
#include <cassert>

enum class FromRedo {No, Yes};

void Execute(AnyCommand cmd, CommandBuffer* commandBuffer, FromRedo fromRedo = FromRedo::No){
  switch(cmd.command.type){
  case CMD_TYPE::NONE:
    break;
  }
}
void Push(CommandBuffer* buffer, AnyCommand cmd){
  assert(cmd.command.type != CMD_TYPE::NONE);
  buffer->allCommands[buffer->index] = cmd;
  buffer->allCommands[buffer->index].command.timestamp = buffer->timestamp;
  buffer->index++;
  buffer->head = buffer->index;
  Execute(cmd, buffer, FromRedo::No);
}

void Undo(CommandBuffer* cmdBuffer){
  if(cmdBuffer->index == 0){
    return;
  }
  cmdBuffer->index--;

  AnyCommand cmd = cmdBuffer->allCommands[cmdBuffer->index];
  assert(cmd.command.type != CMD_TYPE::NONE);
  uint32_t timestamp = cmd.command.timestamp;
  switch(cmd.command.type){
    case CMD_TYPE::NONE:
      break;
    }

  if(cmdBuffer->index > 0){
    if(cmdBuffer->allCommands[cmdBuffer->index - 1].command.timestamp == timestamp){
      Undo(cmdBuffer);
    } 
  }
}

void Redo(CommandBuffer* cmdBuffer){
  AnyCommand cmd = cmdBuffer->allCommands[cmdBuffer->index];
    if(cmdBuffer->index == cmdBuffer->head){
    return;
  }
  assert(cmd.command.type != CMD_TYPE::NONE);
  uint32_t timestamp = cmd.command.timestamp;
  Execute(cmd, cmdBuffer, FromRedo::Yes);

  cmdBuffer->index++;

  if(cmdBuffer->index != cmdBuffer->head){
    AnyCommand nextCommand = cmdBuffer->allCommands[cmdBuffer->index];
    if(nextCommand.command.timestamp == timestamp){
      Redo(cmdBuffer);
    }
  }
}
void ResetCommandBuffer(CommandBuffer* buffer){
  buffer->index = 0;
  buffer->head = 0;
  buffer->timestamp = 0;
}

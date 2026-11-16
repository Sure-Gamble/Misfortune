#pragma once
#include <cstdint>

enum class CMD_TYPE : uint8_t{
  NONE = 0,
};

struct Command {
  CMD_TYPE type = CMD_TYPE::NONE;
  uint32_t timestamp;
};

union AnyCommand {
  Command command;
};

struct CommandBuffer{
  AnyCommand* allCommands;
  int capacity;
  int index;
  int head;
  uint32_t timestamp;
};

void ResetCommandBuffer(CommandBuffer* buffer);
void Push(CommandBuffer* cmdBuffer, AnyCommand cmd);
void Undo(CommandBuffer* cmdBuffer);
void Redo(CommandBuffer* cmdBuffer);

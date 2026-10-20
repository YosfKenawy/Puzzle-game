#include "games/memory_cards/memory_cards.h"

#include <iostream>
#include <memory>

#include "games/memory_cards/memory_cards_level.h"

MemoryCards::MemoryCards() : Game("memorycards", "Memory Cards") {}

int MemoryCards::Attempts() const { return kMemoryCardsAttempts; }

std::string MemoryCards::HowToPlay() const {
  return "TODO(friend): write one line that explains your game.";
}

LevelPtr MemoryCards::CreateLevel(Difficulty difficulty) const {
  return std::make_unique<MemoryCardsLevel>(difficulty);
}

LevelPtr MemoryCards::LoadLevel(const Json& json, Difficulty difficulty) const {
  auto level = std::make_unique<MemoryCardsLevel>(difficulty);
  level->FromJson(json);
  return level;
}

PlayResult MemoryCards::Play(Difficulty, Player&) {
  std::cout << "\nMemory Cards is not implemented yet.\n";
  return {LevelOutcome::kSavedAndQuit, 0};
}

#include "platform.hpp"

#if CPLATFORM_LINUX

bool Platform::Initialize(const char* aplicationName, const int x, const int y, const int width, const int height) {

} 

void Platform::Stop() {

} 

bool Platform::PumpMessages() {

} 

void* Platform::Allocate(const long long int size, const bool aligned) {

} 

void Platform::Free(void* block, const bool aligned) {

} 

void* Platform::MemoryCopy(void* destination, const void* source, const unsigned long int size) {

} 

void* Platform::MemorySet(void* destination, const int value, const unsigned long long int size) {

} 

void Platform::ConsoleWrite(const char* message, const LogLevel level) {

}

void Platform::ConsoleWriteError(const char* message, const LogLevel level) {

} 

double Platform::GetTime() const {

} 

void Platform::PSleep(const unsigned long long int milliseconds) const {

} 

#endif

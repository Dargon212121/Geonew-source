//game structs
#include <map>
template<typename T1, typename T2> bool map_contains_key(T1 map, T2 key) {
	return map.count(key) > 0;
}
#define STATIC_FUNCTION(method_path,name,ta) static inline UnmanagedPointer<ta> name = { METHOD(method_path), UnmanagedStdcall }
#define FIELD(field_path,name,type) type& name() { \
		NP(type) \
		static auto off = OFFSET(field_path); \
		return mem::read<type>(this + off); }
const unsigned short Crc16Table[256] = {
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};
enum QueryTriggerInteraction {
	UseGlobal = 0,
	Ignore = 1,
	Collide = 2,
};

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	body,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

enum PlayerFlags : int
{
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};
class BasePlayer;
BasePlayer* target_ply = nullptr;
class Bone {
public:
	Vector3 position_bebra;
	bool visible;

	Bone() {
		this->position_bebra = Vector3::Zero();
		this->visible = false;
	}
	Bone(Vector3 position) {
		this->position_bebra = position;
		this->visible = false;
	}
	Bone(Vector3 position, bool visible) {
		this->position_bebra = position;
		this->visible = visible;
	}
};

class BoneCache {
public:
	Bone* head;
	Bone* neck;
	Bone* spine4;
	Bone* spine1;
	Bone* l_upperarm;
	Bone* l_forearm;
	Bone* l_hand;
	Bone* r_upperarm;
	Bone* r_forearm;
	Bone* r_hand;
	Bone* pelvis;
	Bone* l_hip;
	Bone* l_knee;
	Bone* l_foot;
	Bone* r_hip;
	Bone* r_knee;
	Bone* r_foot;
	Bone* r_toe;
	Bone* l_toe;

	Vector2 dfc;
	Vector2 forward;
	Quaternion eye_rot;

	BoneCache() {
		head = new Bone();
		neck = new Bone();
		spine4 = new Bone();
		spine1 = new Bone();
		l_upperarm = new Bone();
		l_forearm = new Bone();
		l_hand = new Bone();
		r_upperarm = new Bone();
		r_forearm = new Bone();
		r_hand = new Bone();
		pelvis = new Bone();
		l_hip = new Bone();
		l_knee = new Bone();
		l_foot = new Bone();
		r_hip = new Bone();
		r_knee = new Bone();
		r_foot = new Bone();

		dfc = Vector2();
		forward = { };
		eye_rot = { };
	}
};
struct Explosion {
public:
	std::string name;
	float timeSince;
	Vector3 position;
};
class BulletTracer {
public:
	Vector3 start;
	Vector3 end;
	BulletTracer() {
		this->start = Vector3::Zero();
		this->end = Vector3::Zero();
	}
	BulletTracer(Vector3 st, Vector3 en) {
		this->start = st;
		this->end = en;
	}
};
struct TraceResult {
	float hitDist;
	Vector3 hitPosition;
	Vector3 outVelocity;
	float hitTime;

	TraceResult() {
		this->hitDist = 0.f;
		this->hitPosition = Vector3::Zero();
		this->outVelocity = Vector3::Zero();
		this->hitTime = 0.f;
	}
};
std::map<uint64_t, BoneCache*> cachedBones = std::map<uint64_t, BoneCache*>();

char* memstr(char* haystack, const char* needle, int size) {
	char* p;
	char needlesize = strlen(needle);
	for (p = haystack; p <= (haystack - needlesize + size); p++) {
		if (memcmp(p, needle, needlesize) == 0)
			return p; /* found */
	}
	return NULL;
}
namespace unity {
	// getting camera using header scanning (epic)
	uint64_t get_camera() {
		const auto base = (uint64_t)GetModuleHandleA(xorstr("UnityPlayer.dll"));
		if (!base)
			return 0;
		const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
		const auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);
		uint64_t data_base;
		uint64_t data_size;
		for (int i = 0;;) {
			const auto section = reinterpret_cast<IMAGE_SECTION_HEADER*>(
				base + dos_header->e_lfanew + // nt_header base 
				sizeof(IMAGE_NT_HEADERS64) +  // start of section headers
				(i * sizeof(IMAGE_SECTION_HEADER))); // section header at our index
			if (strcmp((char*)section->Name, xorstr(".data")) == 0) {
				data_base = section->VirtualAddress + base;
				data_size = section->SizeOfRawData;
				break;
			}
			i++;
			if (i >= nt_header->FileHeader.NumberOfSections) {
				Beep(500, 1000);
				return 0;
			}
		}
		uint64_t camera_table = 0;
		const auto camera_string = memstr((char*)data_base, xorstr("AllCameras"), data_size);
		for (auto walker = (uint64_t*)camera_string; walker > 0; walker -= 1) {
			if (*walker > 0x100000 && *walker < 0xF00000000000000) {
				// [[[[unityplayer.dll + ctable offset]]] + 0x30] = Camera
				camera_table = *walker;
				break;
			}
		}
		if (camera_table)
			return camera_table;
		Beep(500, 1000);
		return 0;
	}
	Matrix getViewMatrix() {
		static auto camera_list = get_camera();
		if (!camera_list) return Matrix();

		auto camera_table = *reinterpret_cast<uint64_t*>(camera_list);
		auto cam = *reinterpret_cast<uint64_t*>(camera_table);

		return *reinterpret_cast<Matrix*>(cam + 0x2E4);
	}
}
bool w2s(Vector3 world, Vector2& screen) {
	const auto matrix = unity::getViewMatrix().transpose();

	const Vector3 translation = { matrix[3][0], matrix[3][1], matrix[3][2] };
	const Vector3 up = { matrix[1][0], matrix[1][1], matrix[1][2] };
	const Vector3 right = { matrix[0][0], matrix[0][1], matrix[0][2] };

	const auto w = translation.dot_product(world) + matrix[3][3];

	if (w < 0.1f)
		return false;

	const auto x = right.dot_product(world) + matrix[0][3];
	const auto y = up.dot_product(world) + matrix[1][3];
	screen =
	{
		(Global::ScreenWidth / 2) * (1.f + x / w),
		(Global::ScreenHigh / 2) * (1.f - y / w)
	};

	return true;
}
namespace rust {
	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}
	};
	enum class layer : uint32_t {
		Default = 0,
		TransparentFX = 1,
		Ignore_Raycast = 2,
		Reserved1 = 3,
		Water = 4,
		UI = 5,
		Reserved2 = 6,
		Reserved3 = 7,
		Deployed = 8,
		Ragdoll = 9,
		Invisible = 10,
		AI = 11,
		PlayerMovement = 12,
		Vehicle_Detailed = 13,
		Game_Trace = 14,
		Vehicle_World = 15,
		World = 16,
		Player_Server = 17,
		Trigger = 18,
		Player_Model_Rendering = 19,
		Physics_Projectile = 20,
		Construction = 21,
		Construction_Socket = 22,
		Terrain = 23,
		Transparent = 24,
		Clutter = 25,
		Debris = 26,
		Vehicle_Large = 27,
		Prevent_Movement = 28,
		Prevent_Building = 29,
		Tree = 30,
		Unused2 = 31
	};

	namespace classes {
		enum class HitTestType
		{
			Generic = 0,
			ProjectileEffect = 1,
			Projectile = 2,
			MeleeAttack = 3,
			Use = 4,
		};
	/*	class game_object {
		public:
			template<typename T>
			T get_class()
			{
				return *reinterpret_cast<T*>((uintptr_t)this + 0x30);
			}

			template<typename T>
			T get_class(uint32_t second_offset)
			{
				const auto object = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x30);
				if (!object)
					return nullptr;

				return *reinterpret_cast<T*>(object + second_offset);
			}

			char* get_prefab_name() { return *reinterpret_cast<char**>((uintptr_t)this + 0x60); }

			uint32_t get_tag() { return *reinterpret_cast<uint16_t*>((uintptr_t)this + 0x54); }

			layer get_layer() { return *reinterpret_cast<layer*>(this + 0x50); }
		};*/
		class string {
		public:
			char zpad[0x10];

			int size;
			wchar_t str[128 + 1];
			string(const wchar_t* st) {
				size = min(m_wcslen((wchar_t*)st), 128);
				for (int i = 0; i < size; i++) {
					str[i] = st[i];
				}
				str[size] = 0;
			}
		};
	
	
	}
}
class col {
public:
	float r;
	float g;
	float b;
	float a;
	col(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};
static auto get_Renderers = reinterpret_cast<rust::list<uintptr_t>*(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("SkinnedMultiMesh"), ("get_Renderers"), 0, (""), (""))));
static auto get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Renderer"), ("get_material"), 0, (""), ("UnityEngine"))));
static auto Find = reinterpret_cast<uintptr_t(*)(rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Shader"), ("Find"), 1, (""), ("UnityEngine"))));
static auto SetInt = reinterpret_cast<void(*)(uintptr_t material, rust::classes::string name, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Material"), ("SetInt"), 1, (""), ("UnityEngine"))));
static auto SetFlo = reinterpret_cast<void(*)(uintptr_t material, rust::classes::string name, float value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(("Material"), ("SetFloat"), 1, (""), ("UnityEngine"))));

static auto SetColor = reinterpret_cast<void(*)(uintptr_t material, rust::classes::string name, col value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Material"), xorstr("SetColor"), 2, xorstr("name"), xorstr("UnityEngine"), 1)));

uintptr_t _health = il2cpp::value(xorstr("BaseCombatEntity"), xorstr("_health"));
uintptr_t _displayName = il2cpp::value(xorstr("BasePlayer"), xorstr("_displayName"));
uintptr_t playerModel = il2cpp::value(xorstr("BasePlayer"), xorstr("playerModel"));
uintptr_t newVelocity = il2cpp::value(xorstr("PlayerModel"), xorstr("newVelocity"));
uintptr_t movement = il2cpp::value(xorstr("BasePlayer"), xorstr("movement"));
uintptr_t swimming = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("swimming"));
uintptr_t groundAngleNew = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("groundAngleNew"));
uintptr_t flying = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("flying"));
uintptr_t lastSentTickTime = il2cpp::value(xorstr("BasePlayer"), xorstr("lastSentTickTime"));
uintptr_t landTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("landTime"));
uintptr_t jumpTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("jumpTime"));
uintptr_t groundTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("groundTime"));
uintptr_t gravityMultiplier = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("gravityMultiplier"));
uintptr_t eyes = il2cpp::value(xorstr("BasePlayer"), xorstr("eyes"));
uintptr_t playerFlags = il2cpp::value(xorstr("BasePlayer"), xorstr("playerFlags"));
uintptr_t clientTeam = il2cpp::value(xorstr("BasePlayer"), xorstr("clientTeam"));
uintptr_t lifestate = il2cpp::value(xorstr("BaseCombatEntity"), xorstr("lifestate"));
uintptr_t modelState = il2cpp::value(xorstr("BasePlayer"), xorstr("modelState"));
uintptr_t clActiveItem = il2cpp::value(xorstr("BasePlayer"), xorstr("clActiveItem"));
uintptr_t flags = il2cpp::value(xorstr("ModelState"), xorstr("flags"));
uintptr_t player_inventory = il2cpp::value(xorstr("BasePlayer"), xorstr("inventory"));
uintptr_t userID = il2cpp::value(xorstr("BasePlayer"), xorstr("userID"));
uintptr_t input = il2cpp::value(xorstr("BasePlayer"), xorstr("input"));
uintptr_t recoilAngles = il2cpp::value(xorstr("PlayerInput"), xorstr("recoilAngles"));
uintptr_t hasKeyFocus = il2cpp::value(xorstr("PlayerInput"), xorstr("hasKeyFocus"));
uintptr_t model = il2cpp::value(xorstr("BaseEntity"), xorstr("model"));
uintptr_t clothingMoveSpeedReduction = il2cpp::value(xorstr("BasePlayer"), xorstr("clothingMoveSpeedReduction"));
uintptr_t clothingAccuracyBonus = il2cpp::value(xorstr("BasePlayer"), xorstr("clothingAccuracyBonus"));
uintptr_t repeatDelay = il2cpp::value(xorstr("AttackEntity"), xorstr("repeatDelay"));


void init_bp() {
	repeatDelay = il2cpp::value(xorstr("AttackEntity"), xorstr("repeatDelay"));
	clothingAccuracyBonus = il2cpp::value(xorstr("BasePlayer"), xorstr("clothingAccuracyBonus"));
	clothingMoveSpeedReduction = il2cpp::value(xorstr("BasePlayer"), xorstr("clothingMoveSpeedReduction"));
	hasKeyFocus = il2cpp::value(xorstr("PlayerInput"), xorstr("hasKeyFocus"));
	clActiveItem = il2cpp::value(xorstr("BasePlayer"), xorstr("clActiveItem"));
	player_inventory = il2cpp::value(xorstr("BasePlayer"), xorstr("inventory"));
	input = il2cpp::value(xorstr("BasePlayer"), xorstr("input"));
	_health = il2cpp::value(xorstr("BaseCombatEntity"), xorstr("_health"));
	_displayName = il2cpp::value(xorstr("BasePlayer"), xorstr("_displayName"));
	playerModel = il2cpp::value(xorstr("BasePlayer"), xorstr("playerModel"));
	newVelocity = il2cpp::value(xorstr("PlayerModel"), xorstr("newVelocity"));
	movement = il2cpp::value(xorstr("BasePlayer"), xorstr("movement"));
	swimming = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("swimming"));
	lastSentTickTime = il2cpp::value(xorstr("BasePlayer"), xorstr("lastSentTickTime"));
	playerFlags = il2cpp::value(xorstr("BasePlayer"), xorstr("playerFlags"));
	groundAngleNew = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("groundAngleNew"));
	flying = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("flying"));
	landTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("landTime"));
	jumpTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("jumpTime"));
	groundTime = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("groundTime"));
	gravityMultiplier = il2cpp::value(xorstr("PlayerWalkMovement"), xorstr("gravityMultiplier"));
	eyes = il2cpp::value(xorstr("BasePlayer"), xorstr("eyes"));
	clientTeam = il2cpp::value(xorstr("BasePlayer"), xorstr("clientTeam"));
	lifestate = il2cpp::value(xorstr("BaseCombatEntity"), xorstr("lifestate"));
	userID = il2cpp::value(xorstr("BasePlayer"), xorstr("userID"));
	recoilAngles = il2cpp::value(xorstr("PlayerInput"), xorstr("recoilAngles"));
	modelState = il2cpp::value(xorstr("BasePlayer"), xorstr("modelState"));
	flags = il2cpp::value(xorstr("ModelState"), xorstr("flags"));
	model = il2cpp::value(xorstr("BaseEntity"), xorstr("model"));
	get_Renderers = reinterpret_cast<rust::list<uintptr_t> *(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("SkinnedMultiMesh"), xorstr("get_Renderers"), 0, xorstr(""), xorstr(""))));
	get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Renderer"), ("get_material"), 0, xorstr(""), xorstr("UnityEngine"))));
	Find = reinterpret_cast<uintptr_t(*)(rust::classes::string)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Shader"), xorstr("Find"), 1, xorstr(""), xorstr("UnityEngine"))));
	SetInt = reinterpret_cast<void(*)(uintptr_t material, rust::classes::string name, int value)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Material"), xorstr("SetInt"), 1, xorstr(""), xorstr("UnityEngine"))));


}

namespace unity {
	static auto set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(("UnityEngine.Material::set_shader()")));
	static auto IgnoreLayerCollision = reinterpret_cast<void(*)(rust::layer, rust::layer, bool)>(il2cpp::methods::resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision()")));
	static auto get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Material"), xorstr("get_shader"), 0, xorstr(""), xorstr("UnityEngine"))));


	void init_unity() {
		get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t material)>(*reinterpret_cast<uintptr_t*>(il2cpp::method(xorstr("Material"), xorstr("get_shader"), 0, xorstr(""), xorstr("UnityEngine"))));

		set_shader = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(il2cpp::methods::resolve_icall(("UnityEngine.Material::set_shader()")));
		IgnoreLayerCollision = reinterpret_cast<void(*)(rust::layer, rust::layer, bool)>(il2cpp::methods::resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision()")));


	}
}
class playerwalkmovement {
public:
	void set_swimming(bool flag) {
		*reinterpret_cast<bool*>((uintptr_t)this + swimming) = flag;
	}

	bool get_admin_cheat() {
		return *reinterpret_cast<bool*>((uintptr_t)this + 0x18);
	}

	void set_admin_cheat(bool admin_cheat) {
		*reinterpret_cast<bool*>((uintptr_t)this + 0x18) = admin_cheat;
	}

	bool get_flying() {
		return *reinterpret_cast<bool*>((uintptr_t)this + flying);
	}

	void set_flying(bool fly) {
		*reinterpret_cast<bool*>((uintptr_t)this + flying) = fly;
	}

	void set_ground_angles_new(float angle) {
		*reinterpret_cast<float*>((uintptr_t)this + groundAngleNew) = angle;
	}

	void set_land_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + landTime) = time;
	}

	void set_jump_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + jumpTime) = time;
	}

	void set_ground_time(float time) {
		*reinterpret_cast<float*>((uintptr_t)this + groundTime) = time;
	}

	void set_gravity_multiplier(float multiplier) {
		*reinterpret_cast<float*>((uintptr_t)this + gravityMultiplier) = multiplier;
	}
};

class Mathf {
public:
	static float Abs(float a) {
		return reinterpret_cast<float(_fastcall*)(float)>(Storage::gBase + O::UnityEngine_Mathf::Abs)(a);
	}
	static float Max(float a, float b) {
		return reinterpret_cast<float(_fastcall*)(float, float)>(Storage::gBase + O::UnityEngine_Mathf::Max)(a, b);
	}
};
typedef struct _UncStr
{
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;
class HitTest {
public:

	uintptr_t game_object() {
		return *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x70);
	}

	void set_hit_type(rust::classes::HitTestType hit_type) {
		*reinterpret_cast<int*>((uintptr_t)this + 0x10) = (int)hit_type;
	}

	//void set_ignore_entity(BasePlayer* entity_to_ignore) {
	//	*reinterpret_cast<BasePlayer**>((uintptr_t)this + 0x80) = entity_to_ignore;
	//}

	void set_radius(float radius) {
		*reinterpret_cast<float*>((uintptr_t)this + 0x2C) = radius;
	}

	void set_did_hit(bool did_hit) {
		*reinterpret_cast<bool*>((uintptr_t)this + 0x66) = did_hit;
	}

	//void set_attack_ray(Ray ray) {
	//	*reinterpret_cast<Ray*>((uintptr_t)this + 0x14) = ray;
	//}

	void set_best_hit(bool best_hit) {
		*reinterpret_cast<bool*>((uintptr_t)this + 0x65) = best_hit;
	}

	void set_max_distance(float max_dist) {
		*reinterpret_cast<float*>((uintptr_t)this + 0x34) = max_dist;
	}

	//void set_hit_entity(BasePlayer* entity) {
	//	*reinterpret_cast<BasePlayer**>((uintptr_t)this + 0x88) = entity;
	//}

	//BasePlayer*& get_hit_entity() {
	//	return *reinterpret_cast<BasePlayer**>((uintptr_t)this + 0x88);
	//}

	void set_hit_point(Vector3 hit_point) {
		*reinterpret_cast<Vector3*>((uintptr_t)this + 0x90) = hit_point;
	}

	void set_hit_normal(Vector3 hit_nromal) {
		*reinterpret_cast<Vector3*>((uintptr_t)this + 0x9C) = hit_nromal;
	}
	void set_damage_properties(uintptr_t damage_properties) {
		*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x68) = damage_properties;
	}

};
class Attack {
	Vector3 hitPositionWorld = read(this + O::HitInfo::HitPositionWorld, Vector3);
};
class HitInfo {
};
class BaseCombatEntity
{
public:
	const char* ClassName() {
		if (!this) return "";
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	bool IsPlayer() {
		if (!this) return false;
		return !strcmp(this->ClassName(), xorstr("BasePlayer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayerApex")) ||
			!strcmp(this->ClassName(), xorstr("NPCMurderer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayer")) ||
			!strcmp(this->ClassName(), xorstr("HumanNPC")) ||
			!strcmp(this->ClassName(), xorstr("Scientist")) ||
			!strcmp(this->ClassName(), xorstr("TunnelDweller")) ||
			!strcmp(this->ClassName(), xorstr("HTNPlayer"));
	}
};
class ViewModel {
public:
};
template<typename T>
class List {
public:
	T get(uint32_t idx) {
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T get_value(uint32_t idx) {
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T operator[](uint32_t idx) { return get(idx); }
	const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }
	template<typename F>
	void for_each(const F callback) {
		for (auto i = 0; i < get_size(); i++) {
			auto object = this->get(i);
			if (!object)
				continue;
			callback(object, i);
		}
	}
};

class WeaponData
{
private:
	unsigned short CRC(unsigned char* pcBlock, unsigned short len) {
		unsigned short crc = 0xFFFF;
		while (len--)
			crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];
		return crc;
	}
public:
	uintptr_t entity() {
		return read(this + 0x98, uintptr_t);
	}
	uintptr_t Held() {
		return read(this + O::Item::heldEntity, uintptr_t);//0x98
	}
	int count() {
		return read(this + 0x30, int);
	}
	int GetID()
	{
		DWORD64 Info = read((DWORD64)this + 0x20, DWORD64); // public ItemDefinition info;
		int ID = read(Info + O::ItemDefinition::itemid, int);
		return ID;
	}
	char* ClassName() {
		return (char*)read(read(read(this + O::Item::heldEntity, DWORD64), DWORD64) + 0x10, DWORD64);
	}
	Weapon Info() {
		int ID = GetID();
		for (Weapon k : info) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon{ 0 };
	}
	wchar_t* GetShortName(int* len)
	{
		DWORD64 Info = read(this + 0x20, DWORD64);
		pUncStr Str = ((pUncStr)read(Info + 0x20, DWORD64));
		int leng = read(Str + 0x10, int);
		if (!leng) return nullptr;
		if (len)*len = leng;
		return Str->str;
	}
	wchar_t* GetShortNameName()
	{
		DWORD64 Info = read(this + 0x20, DWORD64);
		pUncStr Str = ((pUncStr)read(Info + 0x20, DWORD64));
		return Str->str;
	}
	int LoadedAmmo()
	{
		const auto Held = read(this + O::Item::heldEntity, DWORD64);
		if (Held <= 0)
			return 0;
		const auto Magazine = read(Held + O::BaseProjectile::primaryMagazine, DWORD64);
		if (Magazine <= 0 || Magazine == 0x3F000000)
		{
			return 0;
		}
		const auto ammoType = read(Magazine + 0x20, DWORD64);
		if (ammoType <= 0 || ammoType == 0x3F000000)
		{
			return 0;
		}
		const int ammo = read(ammoType + 0x18, int);
		return ammo;
	}
	USHORT GetNameHash() {
		int Len;
		UCHAR* ShortName = (UCHAR*)GetShortName(&Len);
		if (ShortName == nullptr) return 0;
		return CRC(ShortName, (Len * 2));
	}
	wchar_t* GetName() {
		DWORD64 Info = read(this + 0x20, DWORD64);
		DWORD64 DispName = read(Info + 0x28, DWORD64);
		pUncStr Str = ((pUncStr)read(DispName + 0x18, DWORD64)); // default
		if (!Str) return nullptr; return Str->str;
	}
	const wchar_t* GetName2() {
		if (this == nullptr) return nullptr;
		DWORD64 held = read(this + O::Item::heldEntity, DWORD64);
		if (!held) return nullptr;

		typedef pUncStr(__stdcall* GetName)(DWORD64);
		pUncStr nm = ((GetName)(Storage::gBase + O::BaseNetworkable::get_ShortPrefabName))(held);
		if (!nm) return nullptr;
		return nm->str;
	}
	int GetUID() {
		return read(this + 0x28, int);
	}
	void SuperBow()
	{
		if (Weapons::SuperBow)
		{
			DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
			write(Held + O::BowWeapon::attackReady, 1, bool); 
			write(Held + O::BowWeapon::arrowBack, 3.f, float); 
		}
	}

	std::string GetAmmoType()
	{
		const auto Held = read(this + O::Item::heldEntity, DWORD64);
		const auto Magazine = read(Held + O::BaseProjectile::primaryMagazine, DWORD64);
		uint64_t item_def = read(Magazine + 0x20, uint64_t);
		uint64_t short_name = read(item_def + 0x20, uint64_t);
		std::wstring wide_name = read(short_name + 0x14, std::wstring);

		if (!wide_name.empty())
			return std::string(wide_name.begin(), wide_name.end()).c_str();

		return "No Ammo";
	}

	void SetAutomatic() {
		if (Weapons::Automatic) {
			DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
			write(Held + O::BaseProjectile::automatic, 1, bool);
		}
	}
	void SuperEoka() {
		if (Weapons::SuperEoka) {
			DWORD64 Held = read(this + O::Item::heldEntity, DWORD64); 
			write(Held + O::BowWeapon::attackReady, 1.f, float); 
			write(Held + O::BowWeapon::wasAiming, true, bool);
		}
	}
	void RapidFire() {
		if (Misc::RapidFire) {
			DWORD64 heldentity = this->entity();
			write(heldentity + O::AttackEntity::repeatDelay, 0.0009f, float);
		}
	}
	void LongHand() {
		DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
		write(Held + O::BaseMelee::maxDistance, 4.5f, float); 
	}
	void FatHand() {
		DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
		write(Held + O::BaseMelee::attackRadius, 15.f, float);
	}
	void RunOnHit() {
		DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
		write(Held + O::BaseMelee::blockSprintOnAttack, 0, int);
	}
};
class SafeExecution {
private:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};
class Physics {
public:
	static bool CheckCapsule(Vector3 start, Vector3 end, float radius, int layerMask, QueryTriggerInteraction queryTriggerInteraction) {
		return SafeExecution::Execute<bool>(Storage::gBase + O::UnityEngine_Physics::CheckCapsule, false, start, end, radius, layerMask, queryTriggerInteraction);
	}
};
class PlayerTick {
public:
	Vector3 positionst() {
		Vector3 th = read(this + 0x20, Vector3);
		if (!th.empty()) {
			return th;
		}
		else { return Vector3::Zero(); }
	}

};
class PlayerEyes{
public:
	Quaternion get_rotation() {
		typedef Quaternion(__stdcall* get_rotation)(PlayerEyes*);
		Quaternion result = ((get_rotation)(Storage::gBase + O::PlayerEyes::get_rotation))(this);
		return result;
	}
	Vector2 get_position() {
		typedef Vector2(__stdcall* get_position)(PlayerEyes*);
		Vector2 result = ((get_position)(Storage::gBase + O::PlayerEyes::get_rotation))(this);
		return result;
	}
};
class PlayerNameID {
public:
	wchar_t* username() {
		auto username = (pUncStr)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x18));
		return username->str;
	}

	unsigned long user_id() {
		return *reinterpret_cast<unsigned long*>((uintptr_t)this + 0x20);
	}
};
class BasePlayer
{
public:

	PlayerEyes* eyest() { return read(this + O::BasePlayer::eyes, PlayerEyes*); }
	float GetHealth() {
		return read(this + O::BaseCombatEntity::_health, float);
	}
	const wchar_t* GetName() {
		pUncStr Str = ((pUncStr)(read(this + O::BasePlayer::_displayName, DWORD64)));
		if (!Str) return StrW(L""); return Str->str;
	}
	Vector3 GetVelocity() {
		DWORD64 PlayerModel = read(this + O::BasePlayer::playerModel, DWORD64);
		return read(PlayerModel + O::PlayerModel::newVelocity, Vector3);
	}
	bool IsVisible() {
		if (AimBot::VisibleCheck) {
			DWORD64 PlayerModel = read(this + O::BasePlayer::playerModel, DWORD64);
			return read(PlayerModel + O::PlayerModel::visible, bool);
		}
		else return true;
	}
	uintptr_t get_player_model() {
		return *reinterpret_cast<uintptr_t*>((uintptr_t)this + playerModel);
	}
	void SetFov()
	{
			auto klass = read(Storage::gBase + 0x3657380, DWORD64);//ConVar.Graphics_TypeInfo
			auto static_fields = read(klass + 0xB8, DWORD64);
			write(static_fields + 0x18, Misc::FovRange, float);
	}
	void Zoom()
	{

		if (FC(user32, GetAsyncKeyState, Misc::Zoomkey))
		{

			auto klass = read(Storage::gBase + 0x3657380, DWORD64); //ConVar.Graphics_TypeInfo //0x2965510 old
			auto static_fields = read(klass + 0xB8, DWORD64);
			write(static_fields + 0x18, Misc::Zoomvalue, float);
		}
		else
		{
			auto klass = read(Storage::gBase + 0x3657380, DWORD64); //ConVar.Graphics_TypeInfo //0x2965510 old
			auto static_fields = read(klass + 0xB8, DWORD64);
			write(static_fields + 0x18, Misc::FovRange, float);
		}
	}
	void InfinityJump()
	{
		INT64 Movement = read((const uintptr_t)this + O::BasePlayer::movement, UINT64);
		write(Movement + O::PlayerWalkMovement::groundAngleNew, Vector3(0, 1000000, 0), Vector3);
		write(Movement + O::PlayerWalkMovement::groundAngle, Vector3(9999999, 9999999, 9999999), Vector3);
	}
	void LongNeck() {
		DWORD64 eyes = read(this + O::BasePlayer::eyes, DWORD64);
		write(eyes + O::PlayerEyes::viewOffset, Vector3(0, 1.5f, 0), Vector3); 
	}
	void LongNeckrLeft()
	{
		if (FC(user32, GetAsyncKeyState, Misc::LongNeckkeyLongNeckLeft))
		{
			DWORD64 eyes = read(this + O::BasePlayer::eyes, DWORD64);
			write(eyes + O::PlayerEyes::viewOffset, Vector3(-1.f, (0), 0), Vector3);
		}
		return;
	}
	void LongNeckright()
	{
		if (FC(user32, GetAsyncKeyState, Misc::LongNeckkey))
		{
			DWORD64 eyes = read(this + O::BasePlayer::eyes, DWORD64);
			write(eyes + O::PlayerEyes::viewOffset, Vector3(1.f, (0), 0), Vector3);
		}
		return;
	}
	float GetJumpHeight() {
		return reinterpret_cast<float(_fastcall*)(BasePlayer*)>(Storage::gBase + O::BasePlayer::GetHeight)(this);
	}
	float GetTickTime() {
		return read(this + O::BasePlayer::lastSentTickTime, float);
	}
	bool IsValid(bool LPlayer = false) {
		return (((LPlayer || PlayerEsp::sleeperignore) ? !HasFlags(16) : true) && !IsDead() && (GetHealth() >= 0.8f));
	}
	bool HasFlags(int Flg) {
		return (read(this + O::BasePlayer::playerFlags, int) & Flg);
	}
	Vector3 GetPosition() {
		return GetPosition(GetTransform(Global::BoneToAim));
	}
	Vector3 GetBoneByID(BoneList BoneID) {
		return GetPosition(GetTransform(BoneID));
	}
	bool IsNpc() {
		DWORD64 PlayerModel = read(this + O::BasePlayer::playerModel, DWORD64);
		return read(PlayerModel + O::PlayerModel::IsNpck__BackingField, bool);
	}
	bool IsDestroyed() {
		if (!this) return true;
		return *reinterpret_cast<bool*>(this + O::BaseNetworkable::IsDestroyedk__BackingField);
	}
	int GetTeamSize()
	{
		DWORD64 ClientTeam = read(this + O::BasePlayer::clientTeam, DWORD64);
		DWORD64 members = read(ClientTeam + 0x30, DWORD64);//	private ListHashSet<ILOD> members; //public PlayerInventory inventory; // 0x28 ���  public List<PlayerTeam.TeamMember> members; // 0x28
		return read(members + 0x18, DWORD64);
	}
	DWORD64 GetTeammateByPos(int Id) {
		DWORD64 ClientTeam = read(this + O::BasePlayer::clientTeam, DWORD64);
		DWORD64 members = read(ClientTeam + 0x30, DWORD64);
		DWORD64 List = read(members + 0x10, DWORD64);
		DWORD64 player = read(List + 0x20 + (Id * 0x8), DWORD64);
		return read(player + 0x20, DWORD64);
	}
	PlayerTick* lastSentTick() { return read(this + O::BasePlayer::lastSentTickTime, PlayerTick*); }
	bool IsTeamMate(DWORD64 SteamID) {
		bool ret = false;

		for (int i = 0; i < 8; i++) {
			if (GetTeammateByPos(i) == SteamID) {
				ret = true;
				break;
			}
		}
		return ret;
	}
	bool IsDead() {
		if (!this) return true;
		return read(this + O::BaseCombatEntity::lifestate, bool);;
	}
	float GetTick() {
		return read(reinterpret_cast<uintptr_t>(this) + O::BasePlayer::lastSentTickTime, float);
	}
	bool HasFlag(int PlayerFlag)
	{
		return (read(this + O::BasePlayer::playerFlags, int) & PlayerFlag);
	}
	bool IsSleeping()
	{
		if (!this) return false;
		return HasFlag(Sleeping);
	}
	bool IsWounded()
	{
		if (!this) return false;
		return HasFlag(Wounded);
	}
	uint64_t& userID() {
		return *reinterpret_cast<uint64_t*>(this + 0x20);
	}
	bool isCached() {
		return map_contains_key(cachedBones, this->GetSteamID());
	}
	BoneCache* bones() {
		return this->isCached() ? cachedBones[this->userID()] : new BoneCache();
	}

	DWORD64 GetSteamID() {
		return read(this + O::BasePlayer::userID, DWORD64);
	}
	bool IsMenu() {
		if (!this) return true;
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		return !(read(Input + O::PlayerInput::hasKeyFocus, bool));
	}
	void SetVA(const Vector2& VA) {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		write(Input + 0x3C, VA, Vector2); //private Vector3 bodyAngles;
	}
	Vector2 viewangles() {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		return read(Input + 0x3C, Vector2); //private Vector3 bodyAngles;
	}
	void AddFlag(int flag) {
		DWORD64 mstate = read(this + O::BasePlayer::modelState, DWORD64);
		int flags = read(mstate + O::ModelState::flags, int);
		write(mstate + O::ModelState::flags, flags |= flag, int);
	}
	void RemoveFlag(int flag) {
		DWORD64 mstate = read(this + O::BasePlayer::modelState, DWORD64);

		int flags = read(mstate + O::ModelState::flags, int);
		write(mstate + O::ModelState::flags, flags &= flag, int);
	}
	void SetRA()
	{
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		Vector2 RA = { 0.f, 0.f };
		write(Input + O::PlayerInput::recoilAngles, RA, Vector2);
	}
	Vector2 GetVA() {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		return read(Input + O::PlayerInput::bodyAngles, Vector2); //private Vector3 bodyAngles;
	}
	Vector2 GetRA() {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		return read(Input + O::PlayerInput::recoilAngles, Vector2);
	}
	WeaponData* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64);
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (WeaponData*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	WeaponData* GetActiveWeapon() {
		int ActUID = read(this + O::BasePlayer::clActiveItem, int);
		if (!ActUID) return nullptr;
		WeaponData* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->GetUID()) {
				return ActiveWeapon;
			}
		return 0;
	}
	List<WeaponData*>* item_list_b() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64); // containerBelt
		return read(Belt + 0x38, List<WeaponData*>*);// public List<Item> itemList;
	}
	List<WeaponData*>* item_list_w() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x30, DWORD64); // containerWear
		return read(Belt + 0x38, List<WeaponData*>*);// public List<Item> itemList;
	}
	void FakeAdmin() {

		int Flags = read(this + O::BasePlayer::playerFlags, int);
		write(this + O::BasePlayer::playerFlags, (Flags |= 4), int);

	}
	void SpiderMan() {
		DWORD64 Movement = read(this + O::BasePlayer::movement, DWORD64);
		write(Movement + O::PlayerWalkMovement::groundAngle, 0.f, float);
		write(Movement + O::PlayerWalkMovement::groundAngleNew, 0.f, float);
	}
	void NoSway() {
		write(this + O::BasePlayer::clothingAccuracyBonus, 1.f, float);
	}
	void NoBlockAiming() {
		write(this + O::BasePlayer::clothingAccuracyBonus, false, bool);
	}
	void NoHeavyReduct() {
		float Reduct = read(this + O::BasePlayer::clothingMoveSpeedReduction, float);
		if (Reduct == 0.f) { write(this + O::BasePlayer::clothingMoveSpeedReduction, -0.1f, float); }
		else if ((Reduct > 0.15f) && (Reduct < 0.35f)) {
			write(this + O::BasePlayer::clothingMoveSpeedReduction, 0.15f, float);
		}
		else if (Reduct > 0.39f) {
			write(this + O::BasePlayer::clothingMoveSpeedReduction, 0.15f, float);
		}
	}
	void Admintime()
	{
		DWORD64 Client = read(Storage::gBase + 0x3653F20, DWORD64); //ConVar_Admin_c*
		DWORD64 pizda = read(Client + 0xB8, DWORD64); //ну тут да можете пастить не маргает лицушка тоже екстернал горобчик ахуенчик
		write(pizda + 0x0, Misc::Time, float);
	}
	void NightMode() {
		if (Visuals::NightMode)
		{
			static DWORD64 dwGameObjectManager = 0;
			UINT64 ObjMgr = read(GetModBase(StrW((L"UnityPlayer.dll"))) + 0x17C1F18, UINT64);
			UINT64 end = read(ObjMgr, UINT64);
			DWORD64 Obj = read(ObjMgr + 0x8, DWORD64); (Obj && (Obj != read(ObjMgr, DWORD64))); Obj = read(Obj + 0x8, DWORD64);
			DWORD64 GameObject = read(Obj + 0x10, DWORD64);
			DWORD64 ObjClass = read(GameObject + 0x30, DWORD64);
			DWORD64 Entity = read(ObjClass + 0x18, DWORD64); 
			DWORD64 Dome = read(Entity + 0x28, DWORD64);
			DWORD64 TodCycle2 = read(Dome + 0x38, DWORD64);
			write(TodCycle2 + 0x10, 01.00f, float);
			return;
		}
		return;
	}
	void SetGravity(float val) {
		DWORD64 Movement = read(this + O::BasePlayer::movement, DWORD64);
		write(Movement + O::PlayerWalkMovement::gravityMultiplier, val, float);
	}

	typedef Vector3(__stdcall* Transform)(UINT64);
	Vector3 GetPosition(ULONG_PTR pTransform) {
		if (!pTransform) return Vector3();
		Transform original = (Transform)(Storage::gBase + O::UnityEngine_Transform::get_position);
		Vector3 res = original(pTransform);
		return res;
	}
	DWORD64 GetTransform(int bone) {
		DWORD64 player_model = read(this + O::BaseEntity::model, DWORD64);// public Model model;_public class BaseEntity : BaseNetworkable, IProvider, ILerpTarget, IPrefabPreProcess // TypeDefIndex: 8714
		DWORD64 boneTransforms = read(player_model + 0x48, DWORD64);//public Transform[] boneTransforms;
		DWORD64 BoneValue = read((boneTransforms + (0x20 + (bone * 0x8))), DWORD64);
		return BoneValue;
	}

};
class Projectile {
public:
	Vector3 currentPosition() { return read(this + O::Projectile::currentPosition, Vector3); }
	void currentPosition(Vector3 d) { write(this + O::Projectile::currentPosition, d, Vector3); }
};
//Base Player
class LPlayerBase 
{
public:
	BasePlayer* BasePlayer = nullptr;
	Matrix4x4* pViewMatrix = nullptr;
	bool WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		if (!pViewMatrix) return false;
		Vector3 TransVec = Vector3(pViewMatrix->_14, pViewMatrix->_24, pViewMatrix->_34);
		Vector3 RightVec = Vector3(pViewMatrix->_11, pViewMatrix->_21, pViewMatrix->_31);
		Vector3 UpVec = Vector3(pViewMatrix->_12, pViewMatrix->_22, pViewMatrix->_32);
		float w = Math::Dot(TransVec, EntityPos) + pViewMatrix->_44;
		if (w < 0.098f) return false;
		float y = Math::Dot(UpVec, EntityPos) + pViewMatrix->_42;
		float x = Math::Dot(RightVec, EntityPos) + pViewMatrix->_41;
		ScreenPos = Vector2((Global::ScreenWidth / 2) * (1.f + x / w), (Global::ScreenHigh / 2) * (1.f - y / w));
		return true;
	}

};


DECLSPEC_NOINLINE void Flex() {
	FC(kernel32, Sleep, 0);
}

LPlayerBase LocalPlayer;


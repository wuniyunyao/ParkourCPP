//
//  Constant.h
//  PaoKu
//
//  Created by YTB on 13-11-26.
//
//

#ifndef PaoKu_Constant_h
#define PaoKu_Constant_h


#define MAP_COUNT (2)

enum SpriteTag
{
    SpriteTagrunner = 0,
    SpriteTagcoin = 1,
    SpriteTagmonster = 2
};
enum Tags
{
	COINTAG,
	ROCKTAG,
};
//static const char backmusic[] = "background.mp3";
#define BACKMUSIC		"background.mp3"
#define JUMPMUSIC		"jump.mp3"
#define CROUCHMUSIC		"crouch.mp3"
#define PICKUPCOINS		"pickup_coin.mp3"
#define SPRITESHEET		"parkour.plist"
#define SPRITEPACKER	"parkour.png"
#define RUNNER0			"runner0.png"
#define RUNNERCROUCH	"runnerCrouch0.png"
#define MAP0			"Map00.png"
#define MAP1			"Map01.png"
#define GROUND0			"Ground00.png"
#define GROUND1			"Ground01.png"
#define COIN0			"coin0.png"
#define ROCKDOWN		"rock.png"
#define ROCKHAT			"hathpace.png"

#endif

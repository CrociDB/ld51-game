const std = @import("std");

const PLAYER_GRAPHICS = [8]u8{
    0b11000011,
    0b10000001,
    0b00100100,
    0b00100100,
    0b00000000,
    0b00100100,
    0b10011001,
    0b11000011,
};

pub const Player = struct {
    x: u16,
    y: u16,
};

pub fn create_player() *Player {
    
    return Player.init(0, 0);
}

pub fn render(player:*Player) void {
    // w4.blit(&PLAYER_GRAPHICS, player.y, player.y, 8, 8, w4.BLIT_1BPP);
    std.debug.print("REndering: {}}", player.x);
}

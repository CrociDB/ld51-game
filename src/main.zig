const std = @import("std");
const Allocator = std.mem.Allocator;

const w4 = @import("wasm4.zig");

const pl = @import("player.zig");

const player = pl.create_player();


export fn update() void {
    update_logic();
    update_graphics();
}

fn update_logic() void {
    const gamepad = w4.GAMEPAD1.*;
    if (gamepad & w4.BUTTON_1 != 0) {
        w4.DRAW_COLORS.* = 4;
    }
}

fn update_graphics() void {
    w4.DRAW_COLORS.* = 2;
    w4.text("Hello from Zig!", 10, 10);
    w4.text("Press X to blink", 16, 90);

    // @compileLog("ASASDASDASD Type: ", @TypeOf(w4));

    pl.render(player);

    // w4.blit(&smiley, 76, 76, 8, 8, w4.BLIT_1BPP);
}

const w = @import("std").os.windows;

//
// FFI
//
const KEYEVENTF_EXTENDEDKEY = 0x0001;
const KEYEVENTF_KEYUP = 0x0002;
const Sleep = w.kernel32.Sleep;
extern "user32" fn GetAsyncKeyState(vKey: c_int) callconv(w.WINAPI) w.SHORT;

// TODO: Use SendInput instead of keybd_event
//
// Reference:
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-keybd_event
extern "user32" fn keybd_event(bVk: w.BYTE, bScan: w.BYTE, dwFlags: w.DWORD, dwExtraInfo: w.ULONG_PTR) callconv(w.WINAPI) void;

//
// Constants
//
const LP = 'U';
const RP = 'I';
const left = 'A';
const right = 'D';
const up = 'W';
const down = 'S';
const upper_right = 'E';
const upper_left = 'Q';

// Press, synthesize press key event
fn p(key: u8) void {
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
}

// Release, synthesize release key event
fn r(key: u8) void {
    keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

// Skip 1 frame
fn f() void {
    Sleep(17);
}

fn get(key: u8) u16 {
    return @as(u16, @bitCast(GetAsyncKeyState(key)));
}

fn double_upper() void {
    r(down);
    f();
    p(LP);
    f();
    r(LP);
    f();
    p(RP);
    f();
    r(RP);
    f();
}

fn release_all_arrows() void {
    var is_delay_needed = false;
    for ([_]u8{ left, right, up, down }) |key| {
        if (0x8001 & get(key) != 0) {
            r(key);
            is_delay_needed = true;
        }
    }
    if (is_delay_needed) {
        f();
    }
}

fn rising_upper(comptime is1P: bool) void {
    const front = if (is1P) right else left;

    p(front);
    f();
    r(front);
    f();
    p(down);
    f();
    p(front);
    p(RP);
    f();
    r(down);
    r(front);
    r(RP);
    f();
}

pub fn main() !void {
    while (true) {
        // TODO: Should not rely on LSB of GetAsyncKeyState
        //
        // Reference:
        //   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
        const upper_right_pressed = 0x1 & get(upper_right) != 0;
        const upper_left_pressed = 0x1 & get(upper_left) != 0;
        const down_pressed = 0x8001 & get(down) != 0;

        if (down_pressed and (upper_left_pressed or upper_right_pressed)) {
            double_upper();
        } else if (upper_right_pressed) {
            release_all_arrows();
            rising_upper(true);
        } else if (upper_left_pressed) {
            release_all_arrows();
            rising_upper(false);
        }
        f();
    }
}
